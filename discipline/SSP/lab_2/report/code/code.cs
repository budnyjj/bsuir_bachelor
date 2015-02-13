  using System;
  using System.IO;
  using System.Collections.Generic;
  using System.ComponentModel;
  using System.Reflection;
  using System.Data;
  using System.Drawing;
  using System.Linq;
  using System.Text;
  using System.Threading.Tasks;
  using System.Windows.Forms;

  namespace lab_2
  {
      public partial class AutomobileForm : Form
      {
          List<Car> carList;
          List<Car> defaultCarList;

          public AutomobileForm()
          {
              InitializeComponent();

              List<string> years = new List<string>();
              int currentYear = DateTime.Now.Year;

              int i = 25;
              while (i > 0) {
                  years.Add(currentYear--.ToString());
                  i--;
              }

              this.yearFromComboBox.DataSource = years;
              this.yearToComboBox.DataSource = new List<string>(years);
          }

          private void openFileButton_Click(object sender, EventArgs e)
          {
              OpenFileDialog openFileDialog = new OpenFileDialog();
              openFileDialog.Filter = "Text files|*.txt";
              openFileDialog.Title = "Select text file with cars";

              if (openFileDialog.ShowDialog() == DialogResult.OK)
              {
                  string openedFilePath = openFileDialog.FileName;

                  string[] lines = {};
                  if (openedFilePath != string.Empty)
                  {
                      lines = System.IO.File.ReadAllLines(openedFilePath);
                  }
                  if (lines.Length != 0)
                  {
                      carList = new List<Car>();

                      this.applyFiltersButton.Enabled = true;
                      this.resetFiltersButton.Enabled = true;
                      this.saveResultsButton.Enabled = true;

                      foreach (string line in lines)
                      {
                          string[] words = line.Split(new char[] { ',' });
                          try
                          {
                              string name = words[0];
                              int year = Convert.ToInt32(words[1]);
                              int price = Convert.ToInt32(words[2]);

                              string imagePath = "";
                              string relativeImagePath = words[3].Trim();
                              if (relativeImagePath.Length != 0)
                              {
                                  string absolutePath = Path.GetDirectoryName(openedFilePath);
                                  imagePath = Path.Combine(absolutePath, relativeImagePath);
                              }
                              carList.Add(new Car(name, year, price, imagePath));
                          }
                          catch (FormatException ex)
                          {
                              MessageBox.Show("FormatException: " + ex.ToString());
                              Application.Exit();
                          }
                          catch (IndexOutOfRangeException ex)
                          {
                              MessageBox.Show("IndexOutOfRangeException: " + ex.ToString());
                              Application.Exit();
                          }
                      }

                      updateCarListBox();
                      defaultCarList = new List<Car>(carList);
                  }
              }
          }

          private void saveResultsButton_Click(object sender, EventArgs e)
          {
              SaveFileDialog saveFileDialog = new SaveFileDialog();
              saveFileDialog.FileName = "filteredCars";
              saveFileDialog.DefaultExt = "txt";
              saveFileDialog.Filter = "Text files|*.txt";

              if (saveFileDialog.ShowDialog() == DialogResult.OK)
              {
                  List<string> cars = new List<string>();
                  foreach (Car car in carList)
                  {
                      cars.Add(car.ToString());
                  }
                  File.WriteAllLines(saveFileDialog.FileName, cars);
              }
          }

          private void autoListBox_SelectedIndexChanged(object sender, EventArgs e)
          {
              int selectedIndex = this.autoListBox.SelectedIndex;
              if (selectedIndex >= 0)
              {
                  this.nameTextBox.Text = carList.ElementAt(selectedIndex).Name;
                  this.yearTextBox.Text = carList.ElementAt(selectedIndex).Year.ToString();
                  this.priceTextBox.Text = carList.ElementAt(selectedIndex).Price.ToString();

                  this.imageBox.Image = null;
                  string imagePath = carList.ElementAt(selectedIndex).ImagePath;

                  try
                  {
                      if (imagePath.Length != 0)
                      {
                          this.noImageLabel.Visible = false;
                          this.imageBox.Image = Image.FromFile(imagePath);
                      }
                      else
                      {
                          this.noImageLabel.Visible = true;
                      }
                  }
                  catch (Exception ex)
                  {
                      MessageBox.Show("Exception: " + ex.ToString());
                      Application.Exit();
                  }
              }
          }

          private void applyFiltersButton_Click(object sender, EventArgs e)
          {
              this.priceErrorLabel.Visible = false;
              this.yearErrorLabel.Visible = false;

              bool isPriceValid = false;
              bool isYearValid = false;

              int priceFrom;
              int priceTo;
              bool isPriceFromIsInt = int.TryParse(this.priceFromTextBox.Text, out priceFrom);
              bool isPriceToIsInt = int.TryParse(this.priceToTextBox.Text, out priceTo);

              if (isPriceFromIsInt && isPriceToIsInt) {
                  if ((priceFrom >= 0) && (priceTo >= priceFrom)) {
                      isPriceValid = true;
                  }
              }

              int yearFrom = 0;
              int yearTo = 0;

              if (this.yearFromComboBox.SelectedIndex >= this.yearToComboBox.SelectedIndex)
              {
                  isYearValid = true;
                  yearFrom = Convert.ToInt32(this.yearFromComboBox.SelectedItem);
                  yearTo = Convert.ToInt32(this.yearToComboBox.SelectedItem);
              }

              if (isPriceValid)
              {
                  if (isYearValid)
                  {
                      applyFilters(priceFrom, priceTo, yearFrom, yearTo);
                  }
                  else
                  {
                      this.yearErrorLabel.Visible = true;
                  }
              }
              else
              {
                  this.priceErrorLabel.Visible = true;
              }
          }

          private void applyFilters(int priceFrom, int priceTo, int yearFrom, int yearTo)
          {
              if (defaultCarList.Count > 0)
              {
                  carList = new List<Car>(defaultCarList);
                  foreach (Car car in defaultCarList)
                  {
                      if ((car.Price < priceFrom) || (car.Price > priceTo) || car.Year < yearFrom || car.Year > yearTo)
                      {
                          carList.Remove(car);
                      }
                  }
                  updateCarListBox();
              }
          }

          private void updateCarListBox()
          {
              this.autoListBox.DataSource = null;
              this.autoListBox.Items.Clear();
              List<string> carNames = carList.Select(o => o.Name).ToList();
              this.autoListBox.DataSource = carNames;
          }

          private void resetFiltersButton_Click(object sender, EventArgs e)
          {
              carList = new List<Car>(defaultCarList);
              updateCarListBox();
          }
      }

      public class Car
      {

          public Car() { }
          public Car(string name, int year, int price, string imagePath)
          {
              this.Name = name;
              this.Year = year;
              this.Price = price;
              this.ImagePath = imagePath;
          }

          private string name;
          public string Name
          {
              get
              {
                  return name;
              }
              set
              {
                  name = value;
              }
          }

          private int year;
          public int Year
          {
              get
              {
                  return year;
              }
              set
              {
                  year = value;
              }
          }

          private int price;
          public int Price
          {
              get
              {
                  return price;
              }
              set
              {
                  price = value;
              }
          }

          private string imagePath;
          public string ImagePath
          {
              get
              {
                  return imagePath;
              }
              set
              {
                  imagePath = value.Trim();
              }
          }

          public override string ToString()
          {
              return this.Name + ", " + this.Year.ToString() + ", " + this.Price.ToString() + ", " + this.ImagePath;
          }
      }
  }
