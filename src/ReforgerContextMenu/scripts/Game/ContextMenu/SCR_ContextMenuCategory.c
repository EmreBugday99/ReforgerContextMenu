[BaseContainerProps(configRoot: true)]
class SCR_ContextMenuCategory : SCR_ContextMenuEntry
{
	[Attribute()]
	protected ref array<ref SCR_ContextMenuEntry> m_aChildEntries;

	[Attribute()]
	protected ref array<ref SCR_ContextMenuCategory> m_aChildCategories;

	int GetChildEntriesAndChildCategories(notnull out array<SCR_ContextMenuEntry> allChildEntries)
	{
		allChildEntries.Clear();

		foreach(SCR_ContextMenuEntry childEntry : m_aChildEntries)
		{
			allChildEntries.Insert(childEntry);
		}

		foreach(SCR_ContextMenuCategory childCategory : m_aChildCategories)
		{
			allChildEntries.Insert(childCategory);
		}

		return allChildEntries.Count();
	}

	void RemoveChild(notnull SCR_ContextMenuEntry entryToRemove)
	{
		SCR_ContextMenuCategory categoryEntry = SCR_ContextMenuCategory.Cast(entryToRemove);

		if (categoryEntry)
			m_aChildCategories.RemoveItem(categoryEntry);
		else
			m_aChildEntries.RemoveItem(entryToRemove);
	}

	bool IsAncestorOf(notnull SCR_ContextMenuCategory otherCategory)
	{
		SCR_ContextMenuCategory iteratedParent = otherCategory.m_ParentCategory;

		while (iteratedParent)
		{
			if (iteratedParent == this)
				return true;

			iteratedParent = iteratedParent.m_ParentCategory;
		}

		return false;
	}

	bool IsSiblingOf(notnull SCR_ContextMenuCategory otherCategory)
	{
		return m_ParentCategory == otherCategory.m_ParentCategory;
	}

	SCR_ContextMenuEntry FindEntry(string entryIdentifier)
	{
		array<SCR_ContextMenuEntry> allChildren = {};
		GetChildEntriesAndChildCategories(allChildren);

		foreach(SCR_ContextMenuEntry iteratedEntry : allChildren)
		{
			if (entryIdentifier == iteratedEntry.m_sIdentifier)
				return iteratedEntry;
		}

		return null;
	}

	protected override void OnHovered()
	{
		super.OnHovered();

		OnPerform();
	}

	protected override void OnPerform()
	{
		super.OnPerform();

		array<SCR_ContextMenuEntry> allChildren = {};
		GetChildEntriesAndChildCategories(allChildren);

		foreach (SCR_ContextMenuEntry childEntry : allChildren)
		{
			childEntry.OnVisible();
		}
	}

	protected override void OnDestroy()
	{
		super.OnDestroy();

		for (int i = m_aChildEntries.Count() - 1; i >= 0; i--)
		{
			SCR_ContextMenuEntry childEntry = m_aChildEntries.Get(i);
			if (childEntry)
				childEntry.Destroy();
		}

		for (int i = m_aChildCategories.Count() - 1; i >= 0; i--)
		{
			SCR_ContextMenuCategory childCategory = m_aChildCategories.Get(i);
			if (childCategory)
				childCategory.Destroy();
		}

		m_aChildEntries.Clear();
		m_aChildCategories.Clear();
	}

	protected override void OnInitialize(int columnIndex, SCR_ContextMenuCategory parentCategory)
	{
		super.OnInitialize(columnIndex, parentCategory);
		columnIndex++;

		foreach (SCR_ContextMenuEntry childEntry : m_aChildEntries)
		{
			typename childEntryType = childEntry.Type();
			if (childEntryType.IsInherited(SCR_ContextMenuCategory))
			{
				Print(childEntryType.ToString() + ": Entries within 'ChildEntries' can't inherit from SCR_ContextMenuCategory. Use 'ChildCategories' instead!", LogLevel.ERROR);
				continue;
			}

			childEntry.OnInitialize(columnIndex, this);
		}

		foreach (SCR_ContextMenuCategory childCategory : m_aChildCategories)
		{
			childCategory.OnInitialize(columnIndex, this);
		}
	}
};