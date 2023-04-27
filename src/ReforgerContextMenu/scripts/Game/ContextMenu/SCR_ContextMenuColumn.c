class SCR_ContextMenuColumn
{
	protected Widget m_wColumnWidget;
	[Attribute()]
	protected ResourceName m_sColumnLayout;

	protected int m_iColumnIndex;
	protected ref array<ref SCR_ContextMenuEntry> m_aEntries = {};

	SCR_ContextMenuEntry FindEntry(string entryIdentifier)
	{
		foreach (SCR_ContextMenuEntry entry : m_aEntries)
		{
			if (entry.GetIdentifier() == entryIdentifier)
				return entry;
		}

		return null;
	}

	void Show()
	{
		if (!m_wColumnWidget)
			return;

		m_wColumnWidget.SetEnabled(true);
		m_wColumnWidget.SetVisible(true);
	}

	void Hide()
	{
		if (!m_wColumnWidget)
			return;

		m_wColumnWidget.SetVisible(false);
		m_wColumnWidget.SetEnabled(false);
	}

	void AddEntry(notnull SCR_ContextMenuEntry entryToAdd)
	{
		m_aEntries.Insert(entryToAdd);

		Widget entryWidget = entryToAdd.GetEntryWidget();
		if (!entryWidget || !m_wColumnWidget)
			return;

		m_wColumnWidget.AddChild(entryWidget);
	}

	void RemoveEntry(notnull SCR_ContextMenuEntry entryToRemove)
	{
		int entryIndex = m_aEntries.Find(entryToRemove);
		if (entryIndex == -1)
			return;

		m_aEntries.Remove(entryIndex);

		Widget entryWidget = entryToRemove.GetEntryWidget();
		if (!entryWidget || !m_wColumnWidget)
			return;

		m_wColumnWidget.RemoveChild(entryWidget);
	}

	void ClearEntries()
	{
		for (int i = m_aEntries.Count() - 1; i >= 0; i--)
		{
			SCR_ContextMenuEntry entry = m_aEntries.Get(i);
			if (entry)
				entry.Destroy();
		}

		m_aEntries.Clear();
	}

	void ~SCR_ContextMenuColumn()
	{
		ClearEntries();
	}
};