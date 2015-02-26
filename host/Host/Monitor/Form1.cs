using System;
using System.Threading;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Monitor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            MonitorBussiness.CEngine.GetClientsRecords();
            MonitorBussiness.CEngine.ShowMonitedClients(listView1);

            Thread newThread = new Thread(new ParameterizedThreadStart(MonitorBussiness.CEngine.ThreadProcClientCheck));
            newThread.Start(listView1);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
        }
    }
}