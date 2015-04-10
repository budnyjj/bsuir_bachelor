namespace TestComponent
{
    partial class Form1
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
            this.originalStringTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.headerStringTextBox = new System.Windows.Forms.TextBox();
            this.footerStringTextBox = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.delimiterStringTextBox = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // originalStringTextBox
            // 
            this.originalStringTextBox.Location = new System.Drawing.Point(15, 89);
            this.originalStringTextBox.Multiline = true;
            this.originalStringTextBox.Name = "originalStringTextBox";
            this.originalStringTextBox.Size = new System.Drawing.Size(1040, 102);
            this.originalStringTextBox.TabIndex = 0;
            this.originalStringTextBox.TextChanged += new System.EventHandler(this.originalStringTextBox_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(9, 54);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(172, 25);
            this.label1.TabIndex = 1;
            this.label1.Text = "Исходный текст";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(10, 215);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(148, 25);
            this.label2.TabIndex = 2;
            this.label2.Text = "Разделитель:";
            // 
            // headerStringTextBox
            // 
            this.headerStringTextBox.Location = new System.Drawing.Point(15, 102);
            this.headerStringTextBox.Multiline = true;
            this.headerStringTextBox.Name = "headerStringTextBox";
            this.headerStringTextBox.Size = new System.Drawing.Size(1040, 107);
            this.headerStringTextBox.TabIndex = 3;
            // 
            // footerStringTextBox
            // 
            this.footerStringTextBox.Location = new System.Drawing.Point(15, 281);
            this.footerStringTextBox.Multiline = true;
            this.footerStringTextBox.Name = "footerStringTextBox";
            this.footerStringTextBox.Size = new System.Drawing.Size(1040, 114);
            this.footerStringTextBox.TabIndex = 4;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.headerStringTextBox);
            this.groupBox1.Controls.Add(this.footerStringTextBox);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.groupBox1.Location = new System.Drawing.Point(31, 328);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1074, 420);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Результаты";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F);
            this.label4.Location = new System.Drawing.Point(10, 235);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(289, 26);
            this.label4.TabIndex = 6;
            this.label4.Text = "Строка после разделителя";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(10, 55);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(254, 26);
            this.label3.TabIndex = 5;
            this.label3.Text = "Строка до разделителя";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.delimiterStringTextBox);
            this.groupBox2.Controls.Add(this.originalStringTextBox);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Location = new System.Drawing.Point(31, 34);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1074, 272);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Исходные данные";
            // 
            // delimiterStringTextBox
            // 
            this.delimiterStringTextBox.Location = new System.Drawing.Point(178, 215);
            this.delimiterStringTextBox.Name = "delimiterStringTextBox";
            this.delimiterStringTextBox.Size = new System.Drawing.Size(877, 31);
            this.delimiterStringTextBox.TabIndex = 3;
            this.delimiterStringTextBox.TextChanged += new System.EventHandler(this.delimiterStringTextBox_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1143, 772);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Использование невизуального компонента";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox originalStringTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox headerStringTextBox;
        private System.Windows.Forms.TextBox footerStringTextBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox delimiterStringTextBox;
    }
}

