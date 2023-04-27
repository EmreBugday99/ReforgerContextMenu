[BaseContainerProps(configRoot: true)]
class SCR_ContextMenuEntry
{
	[Attribute()]
	protected string m_sIdentifier;

	protected ref Widget m_wEntryWidget;
	[Attribute()]
	protected ResourceName m_sEntryLayout;

	protected ref SCR_ContextMenuCategory m_ParentCategory;

	[Attribute()]
	protected ref SCR_UIInfo m_UIInfo;

	[Attribute()]
	protected string m_sEntryNameWidget;
	[Attribute()]
	protected string m_sEntryDescriptionWidget;
	[Attribute()]
	protected string m_sEntryIconDescriptionWidget;

	protected int m_iColumnIndex;
	protected SCR_ContextMenuColumn m_Column;

	[Attribute()]
	protected int m_iOrder;

	string GetIdentifier()
	{
		return m_sIdentifier;
	}

	Widget GetEntryWidget()
	{
		return m_wEntryWidget;
	}

	//------------------------------------------------------------------------------------------------
	void MoveEntry(notnull SCR_ContextMenuColumn newColumn)
	{
		OnMoved(m_Column, newColumn);
	}

	//------------------------------------------------------------------------------------------------
	void Destroy()
	{
		OnDestroy();
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPerform();

	//------------------------------------------------------------------------------------------------
	protected void OnMoved(notnull SCR_ContextMenuColumn oldColumn, notnull SCR_ContextMenuColumn newColumn)
	{
		m_Column = newColumn;
		oldColumn.RemoveEntry(this);
		newColumn.AddEntry(this);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnVisible()
	{
		// TODO: If no Entry Widget, Create one under the Column Widget.
		if (!m_wEntryWidget)
			return;

		m_wEntryWidget.SetEnabled(true);
		m_wEntryWidget.SetVisible(true);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnHidden()
	{
		if (!m_wEntryWidget)
			return;

		m_wEntryWidget.SetVisible(false);
		m_wEntryWidget.SetEnabled(false);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnHovered();

	//------------------------------------------------------------------------------------------------
	protected void OnDestroy()
	{
		if (m_Column)
			m_Column.RemoveEntry(this);
		m_Column = null;

		if (m_ParentCategory)
			m_ParentCategory.RemoveChild(this);
		m_ParentCategory = null;

		if (m_wEntryWidget)
			m_wEntryWidget.RemoveFromHierarchy();
		m_wEntryWidget = null;
	}

	//------------------------------------------------------------------------------------------------
	protected void CreateEntryWidget(Widget parent)
	{
		if (m_wEntryWidget)
			m_wEntryWidget.RemoveFromHierarchy();

		WorkspaceWidget workspace = GetGame().GetWorkspace();
		m_wEntryWidget = workspace.CreateWidgets(m_sEntryLayout, parent);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnInitialize(int columnIndex, SCR_ContextMenuCategory parentCategory)
	{
		m_ParentCategory = parentCategory;
		m_iColumnIndex = columnIndex;
	}
};