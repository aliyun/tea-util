package com.aliyun.teautil.models;

public class TeaUtilException extends RuntimeException{
    public TeaUtilException(String message, Throwable cause) {
        super(message, cause);
    }

    public TeaUtilException(String message) {
        super(message);
    }
}
