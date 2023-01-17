#pragma once
#using <System.dll>

#include<iostream>

namespace ArduinoSensorToSQLv2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Montserrat", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(217, 265);
			this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(237, 60);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(132, 363);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(157, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Estimated Power Bill:";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Desktop;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(181, 82);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(310, 150);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(686, 591);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"MyForm";
			this->Text = L"SmartLight Server Connection";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	String^ ds = "192.168.88.131, 1433";
	String^ userid = "admin2";

	int rowCounterReset = 0;
	int rowCount = 0;
	TimeSpan TS;
	TimeSpan timeOnInput;
	TimeSpan timeOffInput;
	int timeSpanInputFlag = 0;
	int timeOnTurn;
	int timeOffTurn;
	String^ LS;
	double energyBillPrediction;

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		timer1->Start();

	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {


		SerialPort^ mySerial = gcnew SerialPort("COM11", 9600); // Use the serial port "COM3" at 9600 baud
		mySerial->Open();

		String^ data = mySerial->ReadLine();
		array<String^>^ values = data->Split(',');

		//for (int i = 0; i < values->Length; i++) {
		//	Console::WriteLine(values[i]);	
		//}

		//Console::WriteLine(values[1]);

		mySerial->Close();

		if (values[1] == "Turn LED On")
		{
			Console::WriteLine("On");
			SqlConnection^ conDataBase2 = gcnew SqlConnection("Data Source = "+ds+"; Initial Catalog = WebDB; User ID = "+ userid +"; Password = 1234");
			conDataBase2->Open();
			SqlCommand^ cmd2 = gcnew SqlCommand("INSERT INTO LightSensorTimestamps (lightStatus) VALUES ('On')", conDataBase2);
			cmd2->ExecuteNonQuery();
			conDataBase2->Close();
		}

		else if (values[1] == "Turn LED Off")
		{
			Console::WriteLine("Off");
			SqlConnection^ conDataBase2 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
			conDataBase2->Open();
			SqlCommand^ cmd2 = gcnew SqlCommand("INSERT INTO LightSensorTimestamps (lightStatus) VALUES ('Off')", conDataBase2);
			cmd2->ExecuteNonQuery();
			conDataBase2->Close();


			rowCounterReset = 0;

			SqlConnection^ conDataBase5 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
			conDataBase5->Open();
			SqlCommand^ cmd5 = gcnew SqlCommand("DBCC CHECKIDENT('TimeDifferences', RESEED, 0)", conDataBase5);
			cmd5->ExecuteNonQuery();
			conDataBase5->Close();

			SqlConnection^ conDataBase6 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
			conDataBase6->Open();
			SqlCommand^ cmd6 = gcnew SqlCommand("TRUNCATE TABLE TimeDifferences", conDataBase6);
			cmd6->ExecuteNonQuery();
			conDataBase6->Close();

			SqlConnection^ conDataBase4 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
			conDataBase4->Open();
			SqlCommand^ cmd4 = gcnew SqlCommand("SELECT * FROM LightSensorTimestamps", conDataBase4);
			SqlDataReader^ rd4 = cmd4->ExecuteReader();

			rowCount = 0;

			while (rd4->Read() && rowCounterReset == 0)
			{
				rowCount++;
			}

			rowCounterReset = 0;

			std::cout << rowCount << std::endl;//===

			if (rowCounterReset == 0)
			{
				timeOnTurn = 1;
				timeOffTurn = 0;


				for (int i = 1; i <= rowCount; i++)
				{

					SqlConnection^ conDataBase7 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
					conDataBase7->Open();

					SqlCommand^ cmd7 = gcnew SqlCommand("SELECT lightStatus, timestamp FROM LightSensorTimestamps WHERE ID = " + i, conDataBase7);
					SqlDataReader^ rd7 = cmd7->ExecuteReader();
					rd7->Read();
					LS = rd7->GetString(rd7->GetOrdinal("LightStatus"));
					//TS = rd3->GetTimeSpan(rd3->GetOrdinal("TimeStamp"));


					//std::cout << i << std::endl;//====
					//Console::WriteLine(word);//=======


					if (i == 1 && LS == "Off")
					{
						std::cout << "Skipped!" << std::endl;
					}

					else
					{

						if (LS == "On" && timeOnTurn == 1)
						{
							timeOnInput = rd7->GetTimeSpan(rd7->GetOrdinal("TimeStamp"));

							conDataBase7->Close();

							timeOnTurn = 0;
							timeOffTurn = 1;

							//std::cout << "time on input success" << std::endl;//======
						}

						else if (LS == "Off" && timeOffTurn == 1)
						{
							timeOffInput = rd7->GetTimeSpan(rd7->GetOrdinal("TimeStamp"));

							conDataBase7->Close();

							timeOnTurn = 1;
							timeOffTurn = 0;

							timeSpanInputFlag = 1;

							//std::cout << "time off input success" << std::endl;//==========
						}

						if (timeSpanInputFlag == 1)
						{
							SqlConnection^ conDataBase5 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
							conDataBase5->Open();

							SqlCommand^ cmd5 = gcnew SqlCommand("INSERT INTO TimeDifferences (TimeOn, TimeOff) VALUES (@TimeOn, @TimeOff)", conDataBase5);
							cmd5->Parameters->AddWithValue("@TimeOn", timeOnInput);
							cmd5->Parameters->AddWithValue("@TimeOff", timeOffInput);
							cmd5->ExecuteNonQuery();
							conDataBase5->Close();

							timeSpanInputFlag = 0;

							std::cout << "row inserted" << std::endl;
						}

					}

				}
			}

		}

		SqlConnection^ conDataBase3 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
		conDataBase3->Open();
		SqlCommand^ cmd3 = gcnew SqlCommand("SELECT SUM(DATEDIFF(SECOND, TimeOn, TimeOff)) AS timeDiff FROM TimeDifferences", conDataBase3);
		int totalSecs = (int)cmd3->ExecuteScalar();

		//label5->Text = totalSecs.ToString();

		SqlConnection^ conDataBase4 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
		conDataBase4->Open();
		SqlCommand^ cmd4 = gcnew SqlCommand("SELECT CAST(AVG(Rates) AS float) FROM MeralcoRates", conDataBase4);
		double avg = (double)cmd4->ExecuteScalar();

		//label6->Text = avg.ToString();

		energyBillPrediction = (static_cast<double>(totalSecs) / 3600) * 0.01;

		label1->Text = "Estimated Power Bill: P" + energyBillPrediction.ToString();

		SqlConnection^ conDataBase6 = gcnew SqlConnection("Data Source = " + ds + "; Initial Catalog = WebDB; User ID = " + userid + "; Password = 1234");
		conDataBase6->Open();

		SqlCommand^ cmd6 = gcnew SqlCommand("UPDATE EnergyBill SET energyBillVal=@energyBillVal WHERE ID=1", conDataBase6);

		cmd6->Parameters->AddWithValue("@energyBillVal", energyBillPrediction);
		cmd6->ExecuteNonQuery();

		conDataBase6->Close();

		
	}
	};
}
