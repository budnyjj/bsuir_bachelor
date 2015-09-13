using System;
using System.IO;
using System.Text;
using System.Security.Cryptography;


public class ValidatorApp {
    public static void PrintUsage() {
        Console.Write("Usage: checker.exe [-e] [-d] <source> <destination>\n\n" +
                      "Operations:\n" +
                      "    -e: Encrypt\n" +
                      "    -d: Decrypt\n\n" +
                      "Arguments:\n" + 
                      "    <source>: source file\n" + 
                      "    <destination>: destination file\n");
    }

    public static string RequestKey() {
        string key = "";
        while (true) {        
            Console.Write("Please, enter secret key: ");
            key = Console.ReadLine();
            if (String.IsNullOrWhiteSpace(key)) {
                Console.WriteLine("The entered key is empty. Please, try again.");
            } else {
                break;
            }
        }
        
        // Obtain the key from MD5 hash
        byte[] byteKey = new UTF8Encoding().GetBytes(key);
        byte[] byteHashKey =
            ((HashAlgorithm) CryptoConfig.CreateFromName("MD5")).ComputeHash(byteKey);
        string hashKey = BitConverter.ToString(byteHashKey);
        
        return hashKey.Substring(0, KEY_LENGTH);
    }
    
    public static void EncryptFile(string srcFilename, string dstFilename, string key) {
        FileStream srcFStream = new FileStream(srcFilename, FileMode.Open, FileAccess.Read);
        FileStream dstFStream = new FileStream(dstFilename, FileMode.Create, FileAccess.Write);

        DESCryptoServiceProvider DES = new DESCryptoServiceProvider();
        DES.Key = ASCIIEncoding.ASCII.GetBytes(key);
        DES.IV = DES.Key;

        CryptoStream cStream =
            new CryptoStream(dstFStream,
                             DES.CreateEncryptor(),
                             CryptoStreamMode.Write);

        byte[] byteArrayInput = new byte[srcFStream.Length];
        srcFStream.Read(byteArrayInput, 0, byteArrayInput.Length);        
        cStream.Write(byteArrayInput, 0, byteArrayInput.Length);

        cStream.Close();
        srcFStream.Close();
        dstFStream.Close();      
    }

    public static void DecryptFile(string srcFilename, string dstFilename, string key) {
        FileStream srcFStream = new FileStream(srcFilename, FileMode.Open, FileAccess.Read);
        FileStream dstFStream = new FileStream(dstFilename, FileMode.Create, FileAccess.Write);

        DESCryptoServiceProvider DES = new DESCryptoServiceProvider();
        DES.Key = ASCIIEncoding.ASCII.GetBytes(key);
        DES.IV = DES.Key;

        CryptoStream cStream =
            new CryptoStream(srcFStream,
                             DES.CreateDecryptor(),
                             CryptoStreamMode.Read);

        StreamWriter dstStreamWriter = new StreamWriter(dstFStream);
        
        try {
            dstStreamWriter.Write(new StreamReader(cStream).ReadToEnd());
            dstStreamWriter.Flush();       
        } catch (CryptographicException) {
            Console.WriteLine("The entered key is not the correct one. Exit.");
        } finally {
            srcFStream.Close();
            dstStreamWriter.Close();
            dstFStream.Close();
        }
    }
    
    public static void Main(string[] args) {
        if (args.Length != 3) {
            Console.WriteLine("Incorrent number of arguments.");
            PrintUsage();
            return;
        }

        string operation = args[0];
        string srcFileName = args[1];
        string dstFileName = args[2];
        
        if (!File.Exists(srcFileName)) {
            Console.WriteLine("Source file does not exist.");
            return;            
        }

        if (File.Exists(dstFileName)) {
            Console.WriteLine("Destination file already exists.");
            return;            
        }
        
        if (operation.Equals("-e")) {
            // Encrypt file
            string key = RequestKey();
            EncryptFile(srcFileName, dstFileName, key);
        } else if (operation.Equals("-d")) {
            // Decrypt file
            string key = RequestKey();
            DecryptFile(srcFileName, dstFileName, key);
        } else {
            Console.WriteLine("Incorrent operation specified.");
            PrintUsage();            
        }
    }

    private static int KEY_LENGTH = 8;
}