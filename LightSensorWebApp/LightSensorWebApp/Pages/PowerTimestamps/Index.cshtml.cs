using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using System.Data.SqlClient;

namespace LightSensorWebApp.Pages.PowerTimestamps
{

    public class IndexModel : PageModel
    {

        public List<TimestampInfo> listPowerTimestamps = new List<TimestampInfo>();
        public double EnergyBill;

        public void OnGet()
        {

            try
            {

                using (SqlConnection connection = new SqlConnection("Data Source = 192.168.254.100, 1433; Initial Catalog = WebDB; User ID = admin; Password = 1234"))
                {
                    connection.Open();
                    
                    using (SqlCommand command = new SqlCommand("SELECT * FROM TimeDifferences", connection))
                    {
                        using (SqlDataReader reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                TimestampInfo timestampinfo = new TimestampInfo();

                                timestampinfo.id = "" + reader.GetInt32(0);

                                TimeSpan time1 = reader.GetTimeSpan(1);
                                timestampinfo.timeOn = time1.ToString();
                                
                                TimeSpan time2 = reader.GetTimeSpan(2);
                                timestampinfo.timeOff = time2.ToString();


                                listPowerTimestamps.Add(timestampinfo);

                            }    
                        }
                    }

                }

                using (SqlConnection connection = new SqlConnection("Data Source = 192.168.254.100, 1433; Initial Catalog = WebDB; User ID = admin; Password = 1234"))
                {
                    connection.Open();

                    using (SqlCommand command = new SqlCommand("SELECT * FROM EnergyBill", connection))
                    {
                        using (SqlDataReader reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                EnergyBill = reader.GetDouble(1);

                            }
                        }
                    }

                }

            }

            catch (Exception ex)
            {
                Console.WriteLine("Exception: " + ex.ToString());
            }


        }
    }

    public class TimestampInfo
    {
        public String id;
        public String timeOn;
        public String timeOff;
    }


}
