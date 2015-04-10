using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using ComponentLibrary;

namespace TestComponent
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void originalStringTextBox_TextChanged(object sender, EventArgs e)
        {
            processIncomeText(originalStringTextBox.Text, delimiterStringTextBox.Text);
        }

        private void delimiterStringTextBox_TextChanged(object sender, EventArgs e)
        {
            processIncomeText(originalStringTextBox.Text, delimiterStringTextBox.Text);
        }

        private void processIncomeText(String str, String delimiter)
        {
            StringComponent strComponent = new StringComponent();
            headerStringTextBox.Text = strComponent.HeaderOfString(str, delimiter);
            footerStringTextBox.Text = strComponent.FooterOfString(str, delimiter);
        }
    }
}
