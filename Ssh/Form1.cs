using System;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Renci.SshNet;

namespace WindowsFormsAppKcoTestSsh
{
    public partial class Form1 : Form
    {
        private SshClient MonLienSecure;
        public Form1()
        {
            InitializeComponent();
            comboBoxIpAddress.SelectedIndex = 0;
            comboBoxUser.SelectedIndex = 0;
            comboBoxPassword.SelectedIndex = 0;
            comboBoxCommand.SelectedIndex = 0;
        }

        private void buttonSSH_Click(object sender, EventArgs e)
        {
            if (buttonSSH.Text == "Connect")
            {
                string address = comboBoxIpAddress.Text;
                string user = comboBoxUser.Text;
                string password = comboBoxPassword.Text;
                MonLienSecure = new SshClient(address, user, password);
                try
                {
                    MonLienSecure.Connect();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Connection error: \n" + ex.Message);
                    Console.WriteLine("Connection error: \n" + ex.Message);
                }
                if (MonLienSecure.IsConnected)
                {
                    buttonSSH.Text = "Disconnect";
                    comboBoxIpAddress.Enabled = false;
                    comboBoxPassword.Enabled = false;
                    comboBoxUser.Enabled = false;
                    buttonSendCtrlC.Enabled = true;
                    buttonStreamRead.Enabled = true;
                    buttonCommandRead.Enabled = true;
                }
            }
            else
            {
                try
                {
                    MonLienSecure.Disconnect();
                    MonLienSecure.Dispose();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Connection error: \n" + ex.Message);
                    Console.WriteLine("Connection error: \n" + ex.Message);
                }

                buttonSSH.Text = "Connect";
                comboBoxIpAddress.Enabled = true;
                comboBoxPassword.Enabled = true;
                comboBoxUser.Enabled = true;
                buttonSendCtrlC.Enabled = false;
                buttonStreamRead.Enabled = false;
                buttonCommandRead.Enabled = false;
            }
        }

        private void buttonStreamRead_Click(object sender, EventArgs e)
        {
            if (MonLienSecure.IsConnected)
            {
                string str = comboBoxCommand.Text;
                new Task(() => RunCommand(MonLienSecure, "echo temppwd | sudo -S")).Start();
                new Task(() => RunCommand(MonLienSecure, "source CAN_relay.sh")).Start();
            }
        }
        
        private void RunCommand(SshClient LienSsh, String commande)
        {
            var MaCommande = LienSsh.CreateCommand(commande);

            var Resultat = MaCommande.BeginExecute();

            using (var Lecteur = new StreamReader(MaCommande.OutputStream, Encoding.UTF8, true, 1024, true))
            {
                while (!Resultat.IsCompleted || !Lecteur.EndOfStream)
                {
                    var Reponse = Lecteur.ReadLine();
                    if (Reponse != null)
                    {
                        textHistorique.Invoke((MethodInvoker)(() => textHistorique.AppendText(Reponse + Environment.NewLine)));
                    }
                }
            }
            MaCommande.EndExecute(Resultat);
        }

        private void buttonSendCtrlC_Click(object sender, EventArgs e)
        {
            buttonSSH_Click(null, null);
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            textHistorique.Clear();            
        }

        private void buttonQuit_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var maCommande = MonLienSecure.RunCommand(comboBoxCommand.Text);
            textHistorique.AppendText(maCommande.Result + Environment.NewLine);
        }
    }

}
