using Mono.CSharp;
using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

public class ArithmeticChecker {
    private static Double Eval(String expression) {
        return Convert.ToDouble(CSharpEvaluator.Evaluate(expression + ";"));
    }

    public static void PrintUsage() {
        Console.WriteLine("This program performs syntax checking " +
                          "of basic arithmetical equations");
        Console.WriteLine("Usage: arithmetic.exe <equation>\n\n" +
                          "Arguments:\n" + 
                          "    <equation>: arithmetic equation, built from\n" +
                          "                digits and arithmetic operators\n" +
                          "                (+,-,*,/).");
    }

    public static void Main(string[] args) {
        if (args.Length != 1) {
            Console.WriteLine("Incorrent number of arguments.");
            PrintUsage();
            return;
        }

        string source = args[0];
        string arithmPattern = @"\A" +
                               @"[+-]?" +         //Leading sign
                               @"(\d+[\+\-\*\/])*" +  // numbers with operators
                               @"(\d)+" +         // number
                               @"\z";

        if (Regex.IsMatch(source, arithmPattern)) {
            Console.WriteLine(source + " = " + Eval(source));
        } else {
            Console.WriteLine("Incorrect expression.");
        }
    }
}