package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.States.PrgState;
import Models.Types.IType;
import Models.Values.IValue;

public class VarDeclStmt implements IStmt{
    private String name;
    private IType type;

    public VarDeclStmt(String n, IType t ){
        this.name = n;
        this.type = t;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDictionary<String, IValue> symTable = state.getSymTable();

        if(symTable.isDefined(this.name)){
            throw new MyException("A variable has been declared already with the name " + this.name);
        }

        symTable.put(name, type.defaultValue());

        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        typeEnv.put(name,type);
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new VarDeclStmt(this.name, this.type.deepCopy());
    }

    public String toString(){
        return this.type.toString() + " " + this.name;
    }
}
