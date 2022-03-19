package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Types.IntType;
import Models.Values.BoolValue;
import Models.Values.IValue;
import Models.Values.IntValue;

public class RelationalExp implements IExp{

    private IExp exp1;
    private IExp exp2;
    private String sign;

    public RelationalExp(IExp e1, IExp e2, String sign){
        this.exp1 = e1;
        this.exp2 = e2;
        this.sign = sign.replace(" ", "");
    }


    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl) throws MyException {
        IValue exp1Val = this.exp1.eval(tbl);
        if(exp1Val.getType().equals(new IntType())){
            IValue exp2Val = this.exp2.eval(tbl);
            if(exp2Val.getType().equals(new IntType())){
                IntValue exp1IntVal = (IntValue) exp1Val;
                IntValue exp2IntVal = (IntValue) exp2Val;

                switch (this.sign){
                    case "<":
                        return new BoolValue(exp1IntVal.getVal() < exp2IntVal.getVal());
                    case "<=":
                        return new BoolValue(exp1IntVal.getVal() <= exp2IntVal.getVal());
                    case "==":
                        return new BoolValue(exp1IntVal.getVal() == exp2IntVal.getVal());
                    case "!=":
                        return new BoolValue(exp1IntVal.getVal() != exp2IntVal.getVal());
                    case ">":
                        return new BoolValue(exp1IntVal.getVal() > exp2IntVal.getVal());
                    case ">=":
                        return new BoolValue(exp1IntVal.getVal() >= exp2IntVal.getVal());
                    default:
                        throw new MyException("RelationalExp: No such sign exists. Try (<, <=, ==, !=, >, >=).");
                }
            }
            else{
                throw new MyException("RelationalExp: Expression does not return an int type.");
            }
        }
        else{
            throw new MyException("RelationalExp: Expression does not return an int type.");
        }

    }

    @Override
    public IExp deepCopy() {
        return new RelationalExp(this.exp1.deepCopy(), this.exp2.deepCopy(), this.sign);
    }

    public String toString(){
        return "(" + this.exp1 + " " + this.sign + " " + this.exp2 + ")";
    }
}
