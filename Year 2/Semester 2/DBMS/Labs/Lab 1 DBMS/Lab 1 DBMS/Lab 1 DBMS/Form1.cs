using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_1_DBMS
{
    public partial class Form1 : Form
    {
        string connectionString = @"Server=DESKTOP-QMU9GCG\SQLEXPRESS;Database=MovieShowsDBv2;Trusted_Connection=True;";
        SqlConnection conn;
        SqlDataAdapter usersAdapter;
        SqlDataAdapter friendsAdapter;
        SqlCommandBuilder friendsCb;
        DataSet ds;
        BindingSource usersBs, friendsBs;

        public Form1()
        {
            InitializeComponent();
        }

        private void updateBtn_Click(object sender, EventArgs e)
        {
            try
            {

                this.friendsAdapter.Update(this.ds, "Friends");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Something went completely wrong with database connection:");
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }
        }

        private void connectBtn_Click(object sender, EventArgs e)
        {
            try
            {
                conn = new SqlConnection(this.connectionString);

                usersAdapter = new SqlDataAdapter("SELECT * FROM Users", conn);
                friendsAdapter = new SqlDataAdapter("SELECT * FROM Friends", conn);

                friendsCb = new SqlCommandBuilder(friendsAdapter);

                ds = new DataSet();

                usersAdapter.Fill(ds, "Users");
                friendsAdapter.Fill(ds, "Friends");

                friendsBs = new BindingSource();
                usersBs = new BindingSource();

                DataRelation dr_users_userid_friends_userid = new DataRelation("FK_Users_UserId_Friends_UserId", ds.Tables["Users"].Columns["user_id"],
                    ds.Tables["Friends"].Columns["user_id"]);
                DataRelation dr_users_userid_friends_friendid = new DataRelation("FK_Users_UserId_Friends_FriendId", ds.Tables["Users"].Columns["user_id"],
                                        ds.Tables["Friends"].Columns["friend_id"]);

                ds.Relations.Add(dr_users_userid_friends_userid);
                ds.Relations.Add(dr_users_userid_friends_friendid);

                usersBs.DataSource = ds;
                usersBs.DataMember = "Users";

                friendsBs.DataSource = usersBs;
                friendsBs.DataMember = "FK_Users_UserId_Friends_UserId";

                usersDataGridView.DataSource = usersBs;
                friendsDataGridView.DataSource = friendsBs;

            }
            catch (Exception ex)
            {
                Console.WriteLine("Something went completely wrong with database connection:");
                Console.WriteLine(ex.Message);
                Console.WriteLine(ex.StackTrace);
            }

        }

    }
}
