using System;
using System.Data.OleDb;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

namespace YemekSepeti
{
	/// <summary>
	/// Summary description for IpUpdate.
	/// </summary>
	public class IpUpdate : System.Web.UI.Page
	{
		private void Page_Load(object sender, System.EventArgs e)
		{
			// Put user code to initialize the page here
			if (!IsPostBack) {
				if (Request.Params.Count == 0) {
					return;
				}
				Response.Write(Request.Params["restID"].ToString());
				Response.Write(Request.UserHostAddress);
				OleDbConnection conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=G:\calisma\yemeksepeti\host\Data\yemeksepeti.mdb;Persist Security Info=False");
				conn.Open();
				if (conn.State != ConnectionState.Open) {
					Response.Write("açilamadi");
					return;
				}

				using (OleDbCommand comm = conn.CreateCommand()) {
					comm.CommandText = "Select count(*) from Restaurant where RestaurantID = '" + Request.Params["restId"].ToString() +  "'";
					int var = Convert.ToInt32(comm.ExecuteScalar());
					if (var == 0) 
					{
						comm.CommandText = "Insert into Restaurant(RestaurantID, IP, TelefonNo) values('" + 
							Request.Params["restID"].ToString() + "','" + Request.UserHostAddress + "','')";
						comm.ExecuteNonQuery();
					}
					else {
						comm.CommandText = "update Restaurant set IP = '" +  Request.UserHostAddress + "' where RestaurantID = '" + Request.Params["restID"].ToString() + "'";
						comm.ExecuteNonQuery();
					}
				}


				conn.Close();
			}
		}

		#region Web Form Designer generated code
		override protected void OnInit(EventArgs e)
		{
			//
			// CODEGEN: This call is required by the ASP.NET Web Form Designer.
			//
			InitializeComponent();
			base.OnInit(e);
		}
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{    
			this.Load += new System.EventHandler(this.Page_Load);
		}
		#endregion
	}
}
