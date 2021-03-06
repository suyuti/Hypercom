using System;
using System.Threading;
using System.Data;
using System.Data.OleDb;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace MonitorBussiness
{
    public class CEngine
    {
        private static ArrayList g_monitedClients = new ArrayList();
        private static ArrayList g_threads = new ArrayList();

        public static void ShowMonitedClients(ListView lv)
        {
            try {
                lv.BeginUpdate();
                lv.Items.Clear();
                foreach (CMonitedClient client in g_monitedClients) {
                    ListViewItem item = new ListViewItem();
                    item.Text = client.RestauranAdi;
                    item.SubItems.Add(client.durum == 1 ? "Aktif" : "Kapalı");
                    item.SubItems.Add("");
                    item.SubItems.Add(client.POSTelefon);
                    item.SubItems.Add(client.POSIP);
                    if (client.durum == 0) {
                        item.BackColor = System.Drawing.Color.Gray;
                    }
                    lv.Items.Add(item);
                }
            }
            catch(Exception ex) {
            }
            finally {
                lv.EndUpdate();
            }
        }

        public static void GetClientsRecords()
        {
            OleDbConnection conn = null;
            try {
                g_monitedClients.Clear();
                conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=G:\calisma\yemeksepeti\host\Data\yemeksepeti.mdb;Persist Security Info=False");
                conn.Open();
                if (conn.State != ConnectionState.Open) {
                    return;
                }
                using(OleDbCommand comm = conn.CreateCommand()) {
                    comm.CommandText = @"SELECT Restaurantlar.RestaurantID, Restaurantlar.RestaurantAdi, Restaurantlar.POSTelefon, RestaurantIP.IP FROM RestaurantIP INNER JOIN Restaurantlar ON RestaurantIP.RestaurantID = Restaurantlar.RestaurantID where Restaurantlar.aktif = 1;";
                    OleDbDataReader rd = comm.ExecuteReader();
                    while (rd.Read()) {
                        CMonitedClient client = new CMonitedClient();
                        client.RestauranID = rd["RestaurantID"].ToString();
                        client.RestauranAdi = rd["RestaurantAdi"].ToString();
                        client.POSTelefon = rd["POSTelefon"].ToString();
                        client.POSIP = rd["IP"].ToString();
                        client.durum = 0;
                        g_monitedClients.Add(client);
                    }
                    rd.Close();
                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message);
            }
            finally {
                if (conn != null) {
                    conn.Close();
                }
            }
        }

        public static void CheckAlive()
        {
            CPOSConnectionController p = new CPOSConnectionController();
            GetClientsRecords();
            p.IsRestaurantsAlive(g_monitedClients);
        }
        public static void CreateCheckThreads()
        {
            try
            {
                ThreadPool.QueueUserWorkItem() tp = 
            }
            catch (Exception ex) {
                Console.WriteLine(ex.Message);
            }
        }
        public static void ThreadProcClientCheck(object lv)
        {
            while (true) {
                Thread.Sleep(5000);
                Console.WriteLine("Checking...");
                CheckAlive();
                Console.WriteLine("Checked.");
                ShowMonitedClients((ListView)lv);
            }
        }
    }
}