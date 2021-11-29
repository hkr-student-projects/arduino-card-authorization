package com.company;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class EchoServer {

    public static void main(String[] args) {
        // write your code here
        System.out.println("Server is on");
        try (ServerSocket echoServer = new ServerSocket(9222)) {
            Socket clientSocket = echoServer.accept();
            System.out.println("Client is now connected");
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter output = new PrintWriter(clientSocket.getOutputStream(), true);//it passes true and also flush
            String line;// defining a string variable line
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println("Server is still connected: "  + line);//here the message known because both client and server will be run
                output.println(line);//The line is passed here.

            }
        }catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}