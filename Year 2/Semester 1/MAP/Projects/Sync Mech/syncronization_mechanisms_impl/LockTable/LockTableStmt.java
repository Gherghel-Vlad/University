package Model.LockTable;

import Model.IDictionary;
import Model.LockTable.ILockTable;
import Model.Statement.PrgState;
import Model.Statement.Statement;

public class LockTableStmt implements Statement
{
    private String var;
    public LockTableStmt(String name)
    {
        var = name;
    }

    @Override
    public PrgState execute(PrgState ps)
    {
        IDictionary<String,Integer> st = ps.getSymbolT();
        ILockTable<Integer,Integer> lt = ps.getLockTable();

        if (!st.contains(var))
            throw new RuntimeException("Runtime exception !");

        int poz = st.get(var);

        synchronized(lt)
        {
            if (!lt.contains(poz))
                throw new RuntimeException("Runtime exception !");

            if (lt.get(poz) == -1)
                lt.add(poz, ps.getID());
        }

        return null;
    }

    @Override
    public String toString()
    {
        return "Lock(" + var + ")";
    }
}
