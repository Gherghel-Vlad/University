package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Types.BoolType;
import Models.Values.BoolValue;
import Models.Values.IValue;

import java.awt.datatransfer.MimeTypeParseException;

public class LogicExp implements IExp{
    IExp e1;
    IExp e2;
    int op; // 1- and, 2-or

    public LogicExp(IExp e1, IExp e2, int op){
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }

    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl) throws MyException {
        IValue v1, v2;
        v1 = e1.eval(tbl);
        if(v1.getType().equals(new BoolType())){
            v2= e2.eval(tbl);
            if(v2.getType().equals(new BoolType())){
                BoolValue b1,b2;
                b1 = (BoolValue)v1;
                b2 = (BoolValue)v2;

                boolean n1, n2;

                n1 = b1.getVal();
                n2 = b2.getVal();
                switch (op){
                    case 1:
                        return new BoolValue(n1 && n2);
                    case 2:
                        return new BoolValue(n1||n2);
                    default:
                        throw new MyException("Incorrect operation given.");
                }
            }
            else {
                throw new MyException("Second operand is not a bool type.");
            }
        }
        else{
            throw new MyException("First operand is not a bool type.");
        }
    }

    @Override
    public IExp deepCopy() {
        return new LogicExp(this.e1.deepCopy(), this.e2.deepCopy(), this.op);
    }
}
