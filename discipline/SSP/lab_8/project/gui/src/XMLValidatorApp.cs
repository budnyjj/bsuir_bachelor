using System;
using System.IO;
using Gtk;
using Glade;

// Controller class
public class XMLValidatorApp
{
  [Widget]
  Gtk.Window mainWindow;

  [Widget]
  Entry XMLFileEntry;
  
  [Widget]
  Entry schemaFileEntry;
  
  [Widget]
  TextView validationResultTextView;

  [Widget]
  Button openSchemaButton;

  [Widget]
  Button validateButton;
  
  String XMLFilePath = "";
  String schemaFilePath = "";

  XMLValidator validator = new XMLValidator();
  
  public static void Main(string[] args)
  {
    new XMLValidatorApp(args);
  }
  
  public XMLValidatorApp(string[] args)
  {
    Application.Init();
    
    Glade.XML gxml = new Glade.XML(null, "ui.glade", "mainWindow", null);
    gxml.Autoconnect(this);

    Application.Run();
  }

  public void selectXMLFile(object obj, EventArgs args)
  {
    Gtk.FileChooserDialog fc =
      new Gtk.FileChooserDialog("Choose XML file",
                                mainWindow,
                                FileChooserAction.Open,
                                "Cancel", ResponseType.Cancel,
                                "Open", ResponseType.Accept);

    fc.Filter = new FileFilter();
    fc.Filter.AddPattern("*.xml");

    if (fc.Run() == (int) ResponseType.Accept)
      {
        XMLFilePath = fc.Filename;
        XMLFileEntry.Text = XMLFilePath;
        openSchemaButton.Sensitive = true;
      }
    fc.Destroy();
  }

  public void selectSchemaFile(object obj, EventArgs args)
  {
    Gtk.FileChooserDialog fc =
      new Gtk.FileChooserDialog("Choose XML schema file",
                                mainWindow,
                                FileChooserAction.Open,
                                "Cancel", ResponseType.Cancel,
                                "Open", ResponseType.Accept);

    fc.Filter = new FileFilter();
    fc.Filter.AddPattern("*.xsd");

    if (fc.Run() == (int) ResponseType.Accept)
      {
        schemaFilePath = fc.Filename;
        schemaFileEntry.Text = schemaFilePath;
        validateButton.Sensitive = true;
      }
    fc.Destroy();
  }

  public void validateXML(object obj, EventArgs args)
  {
    string validationResult =
      validator.Validate(XMLFilePath, schemaFilePath);
    validationResultTextView.Buffer.Text = validationResult;
  }
  
  public void onWindowDestroy(object obj, EventArgs args)
  {
    Application.Quit();
  }
}