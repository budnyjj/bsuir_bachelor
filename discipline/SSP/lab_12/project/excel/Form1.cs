using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Reflection;

using Excel = Microsoft.Office.Interop.Excel;

namespace excel
{
    public partial class Form1 : Form
    {
        static Excel.Application excel = null;
        static Excel.Workbook workbook = null;
        static Excel.Worksheet sheet = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void calculateButton_Click(object sender, EventArgs e)
        {
            try
            {
                excel.Run("CalculateAndDrawChart");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            try
            {
                sheet.get_Range("H21:H22", Missing.Value).ClearContents();

                try
                {
                    sheet.ChartObjects(1).Delete();
                }
                catch
                {
                    Console.WriteLine("Chart doesn't exist");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void openFileButton_Click(object sender, EventArgs e)
        {
            if (Type.GetTypeFromProgID("Excel.Application") == null)
            {
                MessageBox.Show("Excel doesn't exist on this computer");
                return;
            }

            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Excel Files|*.xlsm";
            openFileDialog.Title = "Open Excel file with Macros";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    excel = new Excel.Application();
                    workbook = excel.Workbooks.Open(openFileDialog.FileName);
                    sheet = workbook.Sheets[1];

                    fileNameLabel.Text = openFileDialog.FileName;

                    fileNameLabel.Visible = true;
                    calculateButton.Enabled = true;
                    refreshButton.Enabled = true;
                    closeFileButton.Enabled = true;
                    openFileButton.Enabled = false;

                    sheet.Activate();
                    workbook.Application.Visible = true;
                    this.Activate();
                }
                catch (Exception)
                {
                    Console.WriteLine("Catched exception.");
                }
            }
        }

        private void closeFileButton_Click(object sender, EventArgs e)
        {
            object missingValue = Missing.Value;
            try
            {
                releaseComObject(sheet);

                workbook.Close(false, missingValue, missingValue);
                releaseComObject(workbook);

                excel.Quit();
                releaseComObject(excel);
            } catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }

            fileNameLabel.Text = null;

            fileNameLabel.Visible = false;
            calculateButton.Enabled = false;
            refreshButton.Enabled = false;
            openFileButton.Enabled = true;
            closeFileButton.Enabled = false;
        }

        private void releaseComObject(object obj)
        {
            try
            {
                System.Runtime.InteropServices.Marshal.ReleaseComObject(obj);
                obj = null;
            }
            catch
            {
                obj = null;
            }
            finally
            {
                GC.Collect();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            fileNameLabel.Visible = false;
            calculateButton.Enabled = false;
            refreshButton.Enabled = false;
            closeFileButton.Enabled = false;
        }
    }
}
