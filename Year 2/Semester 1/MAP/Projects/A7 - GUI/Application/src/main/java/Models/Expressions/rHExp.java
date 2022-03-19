package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.ADTs.MyIHeap;
import Models.Exceptions.MyException;
import Models.Types.IType;
import Models.Types.RefType;
import Models.Values.IValue;
import Models.Values.RefValue;

public class rHExp implements IExp{

    private IExp exp;

    public rHExp(IExp e){
        this.exp = e;
    }


    @Override
    public IValue eval(MyIDictionary<String, IValue> tbl, MyIHeap heap) throws MyException {


        IValue val = this.exp.eval(tbl, heap);

        if(val instanceof RefValue){
            RefValue valRef = (RefValue) val;

            if(heap.isDefined(valRef.getAddress())){
                IValue heapVal = heap.get(valRef.getAddress());

                return heap.get(valRef.getAddress());

            }
            else{
                throw new MyException("rHExp: There is no key with value " + valRef.getAddress() + " in heap.");

            }


        }
        else{
            throw new MyException("rHExp: Expression doesn't return a RefValue.");
        }
    }

    @Override
    public IType typecheck(MyIDictionary<String, IType> typeEnv) throws MyException {
        IType typ=exp.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft =(RefType) typ;
            return reft.getInner();
        } else
            throw new MyException("the rH argument is not a Ref Type");
    }

    @Override
    public IExp deepCopy() {
        return new rHExp(this.exp.deepCopy());
    }

    public String toString(){
        return "rHExp(" + this.exp.toString() +")";
    }
}
