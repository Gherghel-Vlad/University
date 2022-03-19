package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;

public class ArithExp implements IExp{

    private IExp e1;
    private IExp e2;
    private int op; // 1-plus, 2-minus, 3-star, 4-divide
    private char s;

    public ArithExp(char sign, IExp e1, IExp e2){
        this.e1 = e1;
        this.s = sign;
        this.e2 = e2;
        switch (sign){
            case '+':
                this.op = 1;
                break;
            case '-':
                this.op = 2;
                break;
            case '*':
                this.op = 3;
                break;
            case '/':
                this.op = 4;
                break;
            default:
                this.op = 1;
        }
    }


    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl, MyIHeap heap) throws MyException {
        IValue v1, v2;
        v1 = e1.eval(tbl, heap);
        if(v1.getType().equals(new IntType())){
            v2 = e2.eval(tbl, heap);
            if(v2.getType().equals(new IntType())){
                IntValue i1 = (IntValue)v1;
                IntValue i2 = (IntValue)v2;

                int n1, n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                switch (op){
                    case 1:
                        return new IntValue(n1+n2);
                    case 2:
                        return new IntValue(n1-n2);
                    case 3:
                        return new IntValue(n1*n2);
                    case 4:
                        if(n2 == 0) {
                            throw new MyException("Division by zero.");
                        }
                        else{
                            return new IntValue(n1/n2);
                        }
                    default:
                        throw new MyException("Wrong operation for arithmetic expression.");
                }
            }
            else{
                throw new MyException("Second operand is not an integer.");
            }
        }
        else{
            throw new MyException("First operand is not an integer.");
        }
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new IntType())) {
            if(typ2.equals(new IntType())) {
                return new IntType();
            } else
            throw new MyException("second operand is not an integer");
        }else
        throw new MyException("first operand is not an integer");
    }

    @Override
    public IExp deepCopy() {
        return new ArithExp(this.s, this.e1.deepCopy(), this.e2.deepCopy());
    }

    public String toString(){
        return this.e1.toString() + this.s + this.e2.toString();
    }
}
