package Exceptions;

public class RepoException extends Exception {
    private String message;

    public RepoException(String message) {
        this.message = message;
    }

    public String toString() {
        return "RepoException: " + this.message;
    }
}
