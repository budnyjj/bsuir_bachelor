using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;


public class PlusRemover {
    public static void PrintUsage() {
        Console.WriteLine("This program removes leading plus sign " +
                          "from float numbers");
        Console.Write("Usage: plus.exe <number>\n\n" +
                      "Arguments:\n" + 
                      "    <number>: float number\n");
    }
   
    public static void Main(string[] args) {
        if (args.Length != 1) {
            Console.WriteLine("Incorrent number of arguments.");
            PrintUsage();
            return;
        }
        
        string source = args[0];
        string numPattern = @"\A\+?(\d+)[.,](\d+)\z";
        string replace = "$1.$2";

        if (!Regex.IsMatch(source, numPattern)) {
            Console.WriteLine("Please, input a float number.");
            return;
        }
        
        string result = Regex.Replace(source, numPattern, replace);       
        Console.WriteLine("Result: " + result);        
    }
}