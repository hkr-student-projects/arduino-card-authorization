package com.company;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class EchoClient {
    public static void main(String[] args) {
        // write your code here
        System.out.println("EchoClient running....");

        try {
        InetAddress localHost = InetAddress.getLocalHost();
        Socket socket = new Socket(localHost,9222);
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
        BufferedReader buffer = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        System.out.println("Client connected to the server.... ");
        Scanner scanner = new Scanner(System.in);
        String input = null;

        while (!"exist".equalsIgnoreCase(input)){
            System.out.println("What can we do for you: Please enter a text " );
            input = scanner.nextLine();

            out.println(input);
            String response = buffer.readLine();
            System.out.println("Server is responding to the client "  + response);

        }
        }
        catch (Exception ex){
            ex.printStackTrace();
        }
    }
}
