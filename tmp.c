
ExecScan(&node->ss,
    IndexNext(IndexScanState *node)
    bool index_getnext_slot(IndexScanDesc scan, ScanDirection direction, TupleTableSlot *slot))
        ItemPointerData tid = index_getnext_tid(IndexScanDesc scan, ScanDirection direction)
            found = bool btgettuple(IndexScanDesc scan, ScanDirection dir)
                res = bool _bt_first(IndexScanDesc scan, ScanDirection dir)
                    if (!_bt_readpage(scan, dir, offnum, true))
                        return false;
                            // if res = false, save redundant item to scan.
                                return &scan->xs_heaptid; // TODO: return redundundant item and set the flag 
            if (tid == NULL)
				break;
            if (index_fetch_heap(scan, slot))
			    return true;
    return slot;


pg_rewrite_query(Query *query) // 如果有 policy 產生出來的 Query List 也會有 policy
    QueryRewrite()
        fireRIRrules()

PlannedStmt *pg_plan_query(Query *querytree, ...) // 從含 RLS 資訊的 rewritted Query 生出 PlannedStmt 
    plan = PlannedStmt *planner(Query *parse, const char *query_string, int cursorOptions, ParamListInfo boundParams)

ProcessQuery(PlannedStmt* pstmt,...); // pstmt 也要有 RLS flag?
    ExecuteStart(queryDesc)
    ExecutorRun(queryDesc, ForwardScanDirection, 0, true);
        ExecutePlan()
            for loop: slot = ExecProcNode(planstate);

/* TODO: 
    1.save redundant item to scan.   好像存 heapId 就可以了耶
    2. return redundundant item and set the flag 
*/ 
_bt_saveitem(BTScanOpaque so, int itemIndex,
			 OffsetNumber offnum, IndexTuple itup)
{
	BTScanPosItem *currItem = &so->currPos.items[itemIndex];

	currItem->heapTid = itup->t_tid;
	currItem->indexOffset = offnum;
	if (so->currTuples)
	{
		Size		itupsz = IndexTupleSize(itup);

		currItem->tupleOffset = so->currPos.nextTupleOffset;
		memcpy(so->currTuples + so->currPos.nextTupleOffset, itup, itupsz);
		so->currPos.nextTupleOffset += MAXALIGN(itupsz);
	}
}

	currItem = &so->currPos.items[so->currPos.itemIndex];
	scan->xs_heaptid = currItem->heapTid;
	if (scan->xs_want_itup)
		scan->xs_itup = (IndexTuple) (so->currTuples + currItem->tupleOffset);