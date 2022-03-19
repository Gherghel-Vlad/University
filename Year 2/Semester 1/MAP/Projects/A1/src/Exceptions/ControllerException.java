package Exceptions;

public class ControllerException extends Exception {
    private String message;

    public ControllerException(String message){
        this.message = message;
    }

    public String toString(){
        return "ControllerException: " + super.toString();
    }
}