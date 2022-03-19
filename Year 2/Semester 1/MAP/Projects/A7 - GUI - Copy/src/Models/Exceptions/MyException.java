package Models.Exceptions;

public class MyException extends Exception{
    private String message;

    public MyException(String message) {
        this.message = message;
    }

    public String toString() {
        return "MyException: " + this.message;
    }
}
