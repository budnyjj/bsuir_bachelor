namespace lab_2
{
    partial class AutomobileForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.autoListBox = new System.Windows.Forms.ListBox();
            this.openFileButton = new System.Windows.Forms.Button();
            this.filtersGroup = new System.Windows.Forms.GroupBox();
            this.priceFilterGroup = new System.Windows.Forms.GroupBox();
            this.priceToTextBox = new System.Windows.Forms.TextBox();
            this.priceFromTextBox = new System.Windows.Forms.TextBox();
            this.priceErrorLabel = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.yearFilterGroup = new System.Windows.Forms.GroupBox();
            this.yearErrorLabel = new System.Windows.Forms.Label();
            this.yearToComboBox = new System.Windows.Forms.ComboBox();
            this.yearFromComboBox = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.applyFiltersButton = new System.Windows.Forms.Button();
            this.saveResultsButton = new System.Windows.Forms.Button();
            this.resetFiltersButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.autoInformationGroup = new System.Windows.Forms.GroupBox();
            this.noImageLabel = new System.Windows.Forms.Label();
            this.imageBox = new System.Windows.Forms.PictureBox();
            this.priceTextBox = new System.Windows.Forms.TextBox();
            this.yearTextBox = new System.Windows.Forms.TextBox();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.filtersGroup.SuspendLayout();
            this.priceFilterGroup.SuspendLayout();
            this.yearFilterGroup.SuspendLayout();
            this.autoInformationGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageBox)).BeginInit();
            this.SuspendLayout();
            // 
            // autoListBox
            // 
            this.autoListBox.FormattingEnabled = true;
            this.autoListBox.ItemHeight = 25;
            this.autoListBox.Location = new System.Drawing.Point(34, 119);
            this.autoListBox.Name = "autoListBox";
            this.autoListBox.Size = new System.Drawing.Size(400, 579);
            this.autoListBox.TabIndex = 0;
            this.autoListBox.SelectedIndexChanged += new System.EventHandler(this.autoListBox_SelectedIndexChanged);
            // 
            // openFileButton
            // 
            this.openFileButton.Location = new System.Drawing.Point(34, 32);
            this.openFileButton.Name = "openFileButton";
            this.openFileButton.Size = new System.Drawing.Size(400, 65);
            this.openFileButton.TabIndex = 1;
            this.openFileButton.Text = "Open file";
            this.openFileButton.UseVisualStyleBackColor = true;
            this.openFileButton.Click += new System.EventHandler(this.openFileButton_Click);
            // 
            // filtersGroup
            // 
            this.filtersGroup.Controls.Add(this.priceFilterGroup);
            this.filtersGroup.Controls.Add(this.yearFilterGroup);
            this.filtersGroup.Controls.Add(this.applyFiltersButton);
            this.filtersGroup.Controls.Add(this.saveResultsButton);
            this.filtersGroup.Controls.Add(this.resetFiltersButton);
            this.filtersGroup.Controls.Add(this.label1);
            this.filtersGroup.Location = new System.Drawing.Point(934, 32);
            this.filtersGroup.Name = "filtersGroup";
            this.filtersGroup.Size = new System.Drawing.Size(400, 666);
            this.filtersGroup.TabIndex = 2;
            this.filtersGroup.TabStop = false;
            this.filtersGroup.Text = "Filters";
            // 
            // priceFilterGroup
            // 
            this.priceFilterGroup.Controls.Add(this.priceToTextBox);
            this.priceFilterGroup.Controls.Add(this.priceFromTextBox);
            this.priceFilterGroup.Controls.Add(this.priceErrorLabel);
            this.priceFilterGroup.Controls.Add(this.label8);
            this.priceFilterGroup.Location = new System.Drawing.Point(39, 254);
            this.priceFilterGroup.Name = "priceFilterGroup";
            this.priceFilterGroup.Size = new System.Drawing.Size(340, 150);
            this.priceFilterGroup.TabIndex = 5;
            this.priceFilterGroup.TabStop = false;
            this.priceFilterGroup.Text = "Price filter";
            // 
            // priceToTextBox
            // 
            this.priceToTextBox.Location = new System.Drawing.Point(190, 72);
            this.priceToTextBox.Name = "priceToTextBox";
            this.priceToTextBox.Size = new System.Drawing.Size(120, 31);
            this.priceToTextBox.TabIndex = 6;
            this.priceToTextBox.Text = "9500";
            // 
            // priceFromTextBox
            // 
            this.priceFromTextBox.Location = new System.Drawing.Point(36, 72);
            this.priceFromTextBox.Name = "priceFromTextBox";
            this.priceFromTextBox.Size = new System.Drawing.Size(120, 31);
            this.priceFromTextBox.TabIndex = 5;
            this.priceFromTextBox.Text = "5500";
            // 
            // priceErrorLabel
            // 
            this.priceErrorLabel.AutoSize = true;
            this.priceErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.priceErrorLabel.Location = new System.Drawing.Point(30, 46);
            this.priceErrorLabel.Name = "priceErrorLabel";
            this.priceErrorLabel.Size = new System.Drawing.Size(247, 25);
            this.priceErrorLabel.TabIndex = 4;
            this.priceErrorLabel.Text = "Please, check price filter";
            this.priceErrorLabel.Visible = false;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(14, 42);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(0, 25);
            this.label8.TabIndex = 0;
            // 
            // yearFilterGroup
            // 
            this.yearFilterGroup.Controls.Add(this.yearErrorLabel);
            this.yearFilterGroup.Controls.Add(this.yearToComboBox);
            this.yearFilterGroup.Controls.Add(this.yearFromComboBox);
            this.yearFilterGroup.Controls.Add(this.label5);
            this.yearFilterGroup.Location = new System.Drawing.Point(39, 69);
            this.yearFilterGroup.Name = "yearFilterGroup";
            this.yearFilterGroup.Size = new System.Drawing.Size(340, 150);
            this.yearFilterGroup.TabIndex = 4;
            this.yearFilterGroup.TabStop = false;
            this.yearFilterGroup.Text = "Year filter";
            // 
            // yearErrorLabel
            // 
            this.yearErrorLabel.AutoSize = true;
            this.yearErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.yearErrorLabel.Location = new System.Drawing.Point(23, 39);
            this.yearErrorLabel.Name = "yearErrorLabel";
            this.yearErrorLabel.Size = new System.Drawing.Size(248, 25);
            this.yearErrorLabel.TabIndex = 4;
            this.yearErrorLabel.Text = "Please, check year filter ";
            this.yearErrorLabel.Visible = false;
            // 
            // yearToComboBox
            // 
            this.yearToComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.yearToComboBox.Location = new System.Drawing.Point(190, 65);
            this.yearToComboBox.Name = "yearToComboBox";
            this.yearToComboBox.Size = new System.Drawing.Size(120, 33);
            this.yearToComboBox.TabIndex = 3;
            // 
            // yearFromComboBox
            // 
            this.yearFromComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.yearFromComboBox.Location = new System.Drawing.Point(29, 65);
            this.yearFromComboBox.Name = "yearFromComboBox";
            this.yearFromComboBox.Size = new System.Drawing.Size(120, 33);
            this.yearFromComboBox.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(14, 42);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 25);
            this.label5.TabIndex = 0;
            // 
            // applyFiltersButton
            // 
            this.applyFiltersButton.Enabled = false;
            this.applyFiltersButton.ForeColor = System.Drawing.Color.Green;
            this.applyFiltersButton.Location = new System.Drawing.Point(39, 460);
            this.applyFiltersButton.Name = "applyFiltersButton";
            this.applyFiltersButton.Size = new System.Drawing.Size(150, 50);
            this.applyFiltersButton.TabIndex = 3;
            this.applyFiltersButton.Text = "Apply filters";
            this.applyFiltersButton.UseVisualStyleBackColor = true;
            this.applyFiltersButton.Click += new System.EventHandler(this.applyFiltersButton_Click);
            // 
            // saveResultsButton
            // 
            this.saveResultsButton.Enabled = false;
            this.saveResultsButton.ForeColor = System.Drawing.Color.Blue;
            this.saveResultsButton.Location = new System.Drawing.Point(39, 539);
            this.saveResultsButton.Name = "saveResultsButton";
            this.saveResultsButton.Size = new System.Drawing.Size(340, 50);
            this.saveResultsButton.TabIndex = 2;
            this.saveResultsButton.Text = "Save results";
            this.saveResultsButton.UseVisualStyleBackColor = true;
            this.saveResultsButton.Click += new System.EventHandler(this.saveResultsButton_Click);
            // 
            // resetFiltersButton
            // 
            this.resetFiltersButton.Enabled = false;
            this.resetFiltersButton.ForeColor = System.Drawing.Color.Red;
            this.resetFiltersButton.Location = new System.Drawing.Point(229, 460);
            this.resetFiltersButton.Name = "resetFiltersButton";
            this.resetFiltersButton.Size = new System.Drawing.Size(150, 50);
            this.resetFiltersButton.TabIndex = 1;
            this.resetFiltersButton.Text = "Reset";
            this.resetFiltersButton.UseVisualStyleBackColor = true;
            this.resetFiltersButton.Click += new System.EventHandler(this.resetFiltersButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(137, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 25);
            this.label1.TabIndex = 0;
            // 
            // autoInformationGroup
            // 
            this.autoInformationGroup.Controls.Add(this.noImageLabel);
            this.autoInformationGroup.Controls.Add(this.imageBox);
            this.autoInformationGroup.Controls.Add(this.priceTextBox);
            this.autoInformationGroup.Controls.Add(this.yearTextBox);
            this.autoInformationGroup.Controls.Add(this.nameTextBox);
            this.autoInformationGroup.Controls.Add(this.label4);
            this.autoInformationGroup.Controls.Add(this.label3);
            this.autoInformationGroup.Controls.Add(this.label2);
            this.autoInformationGroup.Location = new System.Drawing.Point(482, 32);
            this.autoInformationGroup.Name = "autoInformationGroup";
            this.autoInformationGroup.Size = new System.Drawing.Size(400, 666);
            this.autoInformationGroup.TabIndex = 3;
            this.autoInformationGroup.TabStop = false;
            this.autoInformationGroup.Text = "Car information";
            // 
            // noImageLabel
            // 
            this.noImageLabel.AutoSize = true;
            this.noImageLabel.Location = new System.Drawing.Point(114, 429);
            this.noImageLabel.Name = "noImageLabel";
            this.noImageLabel.Size = new System.Drawing.Size(163, 25);
            this.noImageLabel.TabIndex = 7;
            this.noImageLabel.Text = "No image found";
            this.noImageLabel.Visible = false;
            // 
            // imageBox
            // 
            this.imageBox.Location = new System.Drawing.Point(44, 294);
            this.imageBox.Name = "imageBox";
            this.imageBox.Size = new System.Drawing.Size(300, 300);
            this.imageBox.TabIndex = 6;
            this.imageBox.TabStop = false;
            // 
            // priceTextBox
            // 
            this.priceTextBox.Location = new System.Drawing.Point(119, 200);
            this.priceTextBox.Name = "priceTextBox";
            this.priceTextBox.ReadOnly = true;
            this.priceTextBox.Size = new System.Drawing.Size(236, 31);
            this.priceTextBox.TabIndex = 5;
            // 
            // yearTextBox
            // 
            this.yearTextBox.Location = new System.Drawing.Point(119, 148);
            this.yearTextBox.Name = "yearTextBox";
            this.yearTextBox.ReadOnly = true;
            this.yearTextBox.Size = new System.Drawing.Size(236, 31);
            this.yearTextBox.TabIndex = 4;
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(119, 95);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.ReadOnly = true;
            this.nameTextBox.Size = new System.Drawing.Size(236, 31);
            this.nameTextBox.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(25, 203);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(61, 25);
            this.label4.TabIndex = 2;
            this.label4.Text = "Price";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 151);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 25);
            this.label3.TabIndex = 1;
            this.label3.Text = "Year";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 25);
            this.label2.TabIndex = 0;
            this.label2.Text = "Name";
            // 
            // AutomobileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(1374, 729);
            this.Controls.Add(this.autoInformationGroup);
            this.Controls.Add(this.filtersGroup);
            this.Controls.Add(this.openFileButton);
            this.Controls.Add(this.autoListBox);
            this.MaximizeBox = false;
            this.Name = "AutomobileForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Automobile filter";
            this.filtersGroup.ResumeLayout(false);
            this.filtersGroup.PerformLayout();
            this.priceFilterGroup.ResumeLayout(false);
            this.priceFilterGroup.PerformLayout();
            this.yearFilterGroup.ResumeLayout(false);
            this.yearFilterGroup.PerformLayout();
            this.autoInformationGroup.ResumeLayout(false);
            this.autoInformationGroup.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imageBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox autoListBox;
        private System.Windows.Forms.Button openFileButton;
        private System.Windows.Forms.GroupBox filtersGroup;
        private System.Windows.Forms.Button saveResultsButton;
        private System.Windows.Forms.Button resetFiltersButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button applyFiltersButton;
        private System.Windows.Forms.GroupBox autoInformationGroup;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox yearTextBox;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.PictureBox imageBox;
        private System.Windows.Forms.TextBox priceTextBox;
        private System.Windows.Forms.GroupBox yearFilterGroup;
        private System.Windows.Forms.GroupBox priceFilterGroup;
        private System.Windows.Forms.Label priceErrorLabel;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label yearErrorLabel;
        private System.Windows.Forms.ComboBox yearToComboBox;
        private System.Windows.Forms.ComboBox yearFromComboBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label noImageLabel;
        private System.Windows.Forms.TextBox priceToTextBox;
        private System.Windows.Forms.TextBox priceFromTextBox;
    }
}

