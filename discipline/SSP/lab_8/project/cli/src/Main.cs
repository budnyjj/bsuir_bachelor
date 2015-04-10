using System;
using System.Xml;
using System.Xml.Schema;

public class ValidatorApp
{
  static void validationEventHandler(object sender, ValidationEventArgs e)
  {
    if (e.Severity == XmlSeverityType.Warning)
      {
        Console.Write("WARNING: ");
        Console.WriteLine(e.Message);
      }
    else if (e.Severity == XmlSeverityType.Error)
      {
        Console.Write("ERROR: ");
        Console.WriteLine(e.Message);
      }
  }
  
  public static void Main(string[] args)
  {
    if (args.Length >= 2)
      {
        XmlReaderSettings xmlSettings = new XmlReaderSettings();
        xmlSettings.Schemas.Add("urn:onf:config:yang", args[1]);
        xmlSettings.ValidationType = ValidationType.Schema;
        xmlSettings.ValidationEventHandler +=
          new ValidationEventHandler(validationEventHandler);

        XmlReader rdr = XmlReader.Create(args[0], xmlSettings);
        while (rdr.Read()) { }
      }
    else
      {
        System.Console.WriteLine(
          String.Format("Usage: {0} <xml_file> <schema>", "validator"));
      }
  }
}