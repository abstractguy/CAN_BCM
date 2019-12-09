using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace ProcessStartTest
{
    public partial class StartupForm : Form
    {
        public StartupForm()
        {
            InitializeComponent();
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            OpenFileDialog openDlg = new OpenFileDialog();
            openDlg.Multiselect = false;
            openDlg.Filter = "Executables|*.exe|All Files |*.*";
            openDlg.Title = @"Open executable to run";
            if (openDlg.ShowDialog() == DialogResult.OK)
            {
                txtExecutable.Text = openDlg.FileName;
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            txtResult.Text = string.Empty;
            if (txtExecutable.Text.Trim() != string.Empty)
            {
                StreamReader outputReader = null;
                StreamReader errorReader = null;

                try
                {
                    btnStart.Enabled = false;

                    //Create Process Start information
                    ProcessStartInfo processStartInfo =
                        new ProcessStartInfo(txtExecutable.Text.Trim(), txtParameter.Text.Trim());
                    processStartInfo.ErrorDialog = false;
                    processStartInfo.UseShellExecute = false;
                    processStartInfo.RedirectStandardError = true;
                    processStartInfo.RedirectStandardInput = true;
                    processStartInfo.RedirectStandardOutput = true;

                    //Execute the process
                    Process process = new Process();
                    process.StartInfo = processStartInfo;
                    bool processStarted = process.Start();
                    if (processStarted)
                    {
                        //Get the output stream
                        outputReader = process.StandardOutput;
                        errorReader = process.StandardError;
                        process.WaitForExit();

                        //Display the result
                        string displayText = "Output" + Environment.NewLine + "==============" + Environment.NewLine;
                        displayText += outputReader.ReadToEnd();
                        displayText += Environment.NewLine + "Error" + Environment.NewLine + "==============" +
                                       Environment.NewLine;
                        displayText += errorReader.ReadToEnd();
                        txtResult.Text = displayText;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                finally
                {
                    if(outputReader != null)
                    {
                        outputReader.Close();
                    }
                    if(errorReader != null)
                    {
                        errorReader.Close();
                    }
                    btnStart.Enabled = true;
                }
            }
            else
            {
                MessageBox.Show("Please select executable.");
            }
        }
    }
}