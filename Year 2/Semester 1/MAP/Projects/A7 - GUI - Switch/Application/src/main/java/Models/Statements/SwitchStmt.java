package Models.Statements;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Expressions.IExp;
import Models.Expressions.RelationalExp;
import Models.States.PrgState;
import Models.Types.IType;

public class SwitchStmt implements IStmt{

    IExp exp;
    IExp exp1;
    IExp exp2;
    IStmt stmt1;
    IStmt stmt2;
    IStmt stmt3;

    public SwitchStmt(IExp exp, IExp exp1, IExp exp2, IStmt stmt1, IStmt stmt2, IStmt stmt3){
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.stmt3 = stmt3;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException {

        state.getStk().push(new IfStmt(new RelationalExp(this.exp, this.exp1, "=="), this.stmt1, new IfStmt(new RelationalExp(this.exp, this.exp2, "=="), this.stmt2, this.stmt3)));

        return null;
    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {

        IType type1, type2, type3;

        type1 = this.exp.typecheck(typeEnv);
        type2 = this.exp1.typecheck(typeEnv);
        type3 = this.exp2.typecheck(typeEnv);

        if(!(type1.equals(type2) || type2.equals(type3) || type1.equals(type3))){
            throw new MyException("SwitchStmt: the expressions dont have the same type.");
        }

        this.stmt1.typecheck(typeEnv);
        this.stmt2.typecheck(typeEnv);
        this.stmt3.typecheck(typeEnv);
        return typeEnv;
    }

    @Override
    public IStmt deepCopy() {
        return new SwitchStmt(this.exp.deepCopy(), this.exp1.deepCopy(), this.exp2.deepCopy(), this.stmt1.deepCopy(), this.stmt2.deepCopy(), this.stmt3.deepCopy());
    }

    public String toString(){
        return "switch("+this.exp.toString()+ ") (case " + this.exp1.toString() + ": " + this.stmt1.toString()+") (case " + this.exp2.toString()+ ": " +this.stmt2.toString() + ") (default: " + this.stmt3.deepCopy() + ")";
    }
}
