package Models.Expressions;

import Models.ADTs.MyIDictionary;
import Models.Exceptions.MyException;
import Models.Values.IValue;


public interface IExp {
    IValue eval(MyIDictionary<String, IValue> tbl) throws MyException;


    public IExp deepCopy();
}
