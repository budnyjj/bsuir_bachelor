using System;
using System.Xml;
using System.Xml.Schema;

public class XMLValidator
{
  string validationResult = "";
  
  void validationEventHandler(object sender, ValidationEventArgs e)
  {
    if (e.Severity == XmlSeverityType.Warning)
      {
        validationResult += "WARNING: " + e.Message + "\n\n" ;
      }
    else if (e.Severity == XmlSeverityType.Error)
      {
        validationResult += "ERROR: " + e.Message + "\n\n";
      }
  }  
  
  public string Validate(String XMLFilePath, String schemaFilePath)
  {
    XmlReaderSettings xmlSettings = new XmlReaderSettings();

    try
      {   
        xmlSettings.Schemas.Add(null, schemaFilePath);
      }
    catch (XmlException e)
      {
        return "ERROR: Incorrect XML schema file.\n\n" +
               "Stack trace: " + e.ToString();
      }

    xmlSettings.ValidationType = ValidationType.Schema;
    xmlSettings.ValidationEventHandler +=
      new ValidationEventHandler(validationEventHandler);

    validationResult = "";

    XmlReader rdr = XmlReader.Create(XMLFilePath, xmlSettings);

    try
      {   
        while (rdr.Read()) { }
      }
    catch (XmlException e)
      {
        return "ERROR: Incorrect XML file.\n\n" +
               "Stack trace: " + e.ToString();
      }
    
    return validationResult;
  }
}