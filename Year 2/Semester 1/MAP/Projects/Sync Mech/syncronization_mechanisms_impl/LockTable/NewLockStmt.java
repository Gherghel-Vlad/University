package Model.LockTable;

import Model.IDictionary;
import Model.LockTable.ILockTable;
import Model.Statement.PrgState;
import Model.Statement.Statement;

public class NewLockStmt implements Statement
{
    private String var;
    private int nextFree = 0;

    public NewLockStmt(String v)
    {
        var = v;
    }

    public PrgState execute(PrgState ps)
    {
        ILockTable<Integer, Integer> lt = ps.getLockTable();
        IDictionary<String, Integer> st = ps.getSymbolT();
        synchronized (lt)
        {
            lt.add(nextFree, -1);
        }
        if (st.contains(var))
        {
            st.update(var, nextFree);
        }
        else
        {
            st.add(var, nextFree);
        }
        nextFree++;
        return null;
    }

    @Override
    public String toString()
    {
        return "NewLock(" + var +")";
    }
}
