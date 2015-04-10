using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace ComponentLibrary
{
    public partial class StringComponent : Component
    {
        public StringComponent()
        {
            InitializeComponent();
        }

        public StringComponent(IContainer container)
        {
            container.Add(this);
            InitializeComponent();
        }

        public String HeaderOfString(String str, String delimiter)
        {
            if (str == null || str.Length == 0)
            {
                return "";
            }
            else
            {
                if (delimiter == null || delimiter.Length == 0)
                {
                    return str;
                }
                else
                {

                    if (str.Contains(delimiter))
                    {
                        return str.Substring(0, str.IndexOf(delimiter));
                    }
                    else
                    {
                        return str;
                    }
                }
            }
        }

        public String FooterOfString(String str, String delimiter)
        {
            if (str == null || str.Length == 0)
            {
                return "";
            }
            else
            {
                if (delimiter == null || delimiter.Length == 0)
                {
                    return "";
                }
                else
                {
                    if (str.Contains(delimiter))
                    {
                        return str.Substring(str.IndexOf(delimiter) + delimiter.Length);
                    }
                    else
                    {
                        return "";
                    }
                }
            }
        }
    }
}
