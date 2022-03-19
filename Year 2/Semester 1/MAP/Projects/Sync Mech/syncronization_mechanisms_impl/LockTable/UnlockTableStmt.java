package Model.LockTable;

import Model.IDictionary;
import Model.LockTable.ILockTable;
import Model.Statement.PrgState;
import Model.Statement.Statement;

public class UnlockTableStmt implements Statement
{
    private String var;
    public UnlockTableStmt(String name)
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
            if (lt.get(poz) == ps.getID())
                lt.add(poz, -1);
        }
        return null;
    }

    @Override
    public String toString()
    {
        return "Unlock(" + var + ")";
    }
}
