#pragma once

namespace DatabaseConnection2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;


	/// <summary>
	/// Summary for dataTable
	/// </summary>
	public ref class dataTable : public System::Windows::Forms::Form
	{
	public:
		dataTable(void)
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
		~dataTable()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataTimeStamp;

	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
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
			this->dataTimeStamp = (gcnew System::Windows::Forms::DataGridView());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTimeStamp))->BeginInit();
			this->SuspendLayout();
			// 
			// dataTimeStamp
			// 
			this->dataTimeStamp->AllowUserToAddRows = false;
			this->dataTimeStamp->AllowUserToDeleteRows = false;
			this->dataTimeStamp->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataTimeStamp->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataTimeStamp->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1,
					this->Column2, this->Column3
			});
			this->dataTimeStamp->Location = System::Drawing::Point(12, 12);
			this->dataTimeStamp->Name = L"dataTimeStamp";
			this->dataTimeStamp->ReadOnly = true;
			this->dataTimeStamp->RowHeadersVisible = false;
			this->dataTimeStamp->Size = System::Drawing::Size(608, 373);
			this->dataTimeStamp->TabIndex = 0;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 2000;
			this->timer1->Tick += gcnew System::EventHandler(this, &dataTable::timer1_Tick);
			// 
			// Column1
			// 
			this->Column1->DataPropertyName = L"sensor1";
			this->Column1->HeaderText = L"Light Sensor Value";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			// 
			// Column2
			// 
			this->Column2->DataPropertyName = L"sensor2";
			this->Column2->HeaderText = L"Room Light Status";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->DataPropertyName = L"time stamp";
			this->Column3->HeaderText = L"Time Stamp";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// dataTable
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 397);
			this->Controls->Add(this->dataTimeStamp);
			this->Name = L"dataTable";
			this->Text = L"Room Light Monitoring";
			this->Load += gcnew System::EventHandler(this, &dataTable::dataTable_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataTimeStamp))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void dataTable_Load(System::Object^ sender, System::EventArgs^ e) {

		timer1->Start();

	}
	
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		//String^ conString = "Data Source=DESKTOP-K5IK85D;Initial Catalog=Testing;Integrated Security=True";

		String^ conString = "Data Source=192.168.254.100, 1433;Initial Catalog=Testing; User ID = 'admin'; Password = '1234'";

		//use "Data Source=192.168.254.100, 1433;Initial Catalog=Testing; User ID = 'admin'; Password = '1234'" when running the code on another device in the network

		SqlConnection^ conDataBase = gcnew SqlConnection(conString);
		SqlCommand^ cmdDataBase = gcnew SqlCommand("select * from dbo.roomLight;", conDataBase);
		SqlDataReader^ myReader;

		SqlDataAdapter^ sda = gcnew SqlDataAdapter();
		sda->SelectCommand = cmdDataBase;
		DataTable^ dbdataset = gcnew DataTable();
		sda->Fill(dbdataset);
		BindingSource^ bSource = gcnew BindingSource();

		bSource->DataSource = dbdataset;
		dataTimeStamp->DataSource = bSource;
		sda->Update(dbdataset);

		this->dataTimeStamp->Columns[2]->Visible = false;

		timer1->Start();

	}
};
}
