#include <random>
#include <chrono>
#include <functional>
#include <vector>
#include "matrix.h"
#include "polynom.h"
#include <algorithm>
QSMatrix<polynom>* dPdt;

std::vector<double> runge(const double& h, const std::vector<std::function<double(const std::vector<double>&)>> &f, const std::vector<double>& x0, int cof = 1)
{

	std::vector<std::vector<double>> coeff;
	for (int i = 0; i < f.size(); i++)
	{
		std::vector<double> tmp(4);
		tmp[0] = f[i](x0);
		std::vector<double> tmp_vec;
		for (const auto& el : x0)
			tmp_vec.emplace_back(el + (h / 2.0)*tmp[0]);
		tmp[1] = f[i](tmp_vec);
		std::vector<double> tmp_vec1;
		for (const auto& el : tmp_vec)
			tmp_vec1.emplace_back(el + (h / 2.0)*tmp[1]);
		tmp[2] = f[i](tmp_vec1);
		std::vector<double> tmp_vec2;
		for (const auto& el : tmp_vec1)
			tmp_vec2.emplace_back(el + h * tmp[2]);
		tmp[3] = f[i](tmp_vec2);
		coeff.emplace_back(tmp);
	}
	std::vector<double> xi(f.size());
	for (int i = 0; i < f.size(); i++)
	{
		xi[i] = x0[i] + cof * (h / 6.0)*(coeff[i][0] + coeff[i][1] * 2 + coeff[i][2] * 2 + coeff[i][3]);
	}
	return xi;
}

auto get_syste(QSMatrix<polynom>& dPdt) {
	std::vector<std::function<double(const std::vector<double>&)>> system_p;
	for (int i = 0; i < dPdt.get_rows(); i++) {
		system_p.emplace_back(dPdt(0,i).gen_getVal());
	}
	for (int i = 1; i < dPdt.get_cols(); i++) {
		system_p.emplace_back(dPdt(i, dPdt.get_rows() - 1).gen_getVal());
	}
	return system_p;
}


namespace Computational_Methods_Lab1
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			comboBoxSize->SelectedIndex = 0;
			
			textBox1->Text = "0,0";
			textBox2->Text = "6,28";
			textBox3->Text = "0,1";
			chart1->ChartAreas[0]->AxisY->Maximum = 5;
			dataGridView1->AllowUserToAddRows = false;
			dataGridView2->AllowUserToAddRows = false;
			dataGridView3->AllowUserToAddRows = false;
			dataGridView4->AllowUserToAddRows = false;
			dataGridView5->AllowUserToAddRows = false;
			dataGridView1->RowsDefaultCellStyle->SelectionBackColor = System::Drawing::Color::Transparent;
			dataGridView1->RowsDefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			dataGridView2->RowsDefaultCellStyle->SelectionBackColor = System::Drawing::Color::Transparent;
			dataGridView2->RowsDefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			dataGridView3->RowsDefaultCellStyle->SelectionBackColor = System::Drawing::Color::Transparent;
			dataGridView3->RowsDefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			dataGridView4->RowsDefaultCellStyle->SelectionBackColor = System::Drawing::Color::Transparent;
			dataGridView4->RowsDefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			dataGridView5->RowsDefaultCellStyle->SelectionBackColor = System::Drawing::Color::Transparent;
			dataGridView5->RowsDefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			dataGridView6->RowsDefaultCellStyle->SelectionBackColor = System::Drawing::Color::Transparent;
			dataGridView6->RowsDefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
			//chart1->Series[0]->ChartType = DataVisualization::Charting::SeriesChartType::Spline;
			//chart1->Series[1]->ChartType = DataVisualization::Charting::SeriesChartType::Spline;
			
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::ComboBox^  comboBoxSize;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::DataGridView^  dataGridView3;
	private: System::Windows::Forms::DataGridView^  dataGridView4;
	private: System::Windows::Forms::DataGridView^  dataGridView5;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::DataGridView^  dataGridView6;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			this->comboBoxSize = (gcnew System::Windows::Forms::ComboBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView5 = (gcnew System::Windows::Forms::DataGridView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView6 = (gcnew System::Windows::Forms::DataGridView());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView6))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// comboBoxSize
			// 
			this->comboBoxSize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBoxSize->FormattingEnabled = true;
			this->comboBoxSize->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"1", L"2", L"3", L"4", L"5" });
			this->comboBoxSize->Location = System::Drawing::Point(28, 27);
			this->comboBoxSize->Name = L"comboBoxSize";
			this->comboBoxSize->Size = System::Drawing::Size(75, 24);
			this->comboBoxSize->TabIndex = 1;
			this->comboBoxSize->SelectedValueChanged += gcnew System::EventHandler(this, &MyForm::comboBoxSize_SelectedValueChanged);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->BackgroundColor = System::Drawing::Color::Goldenrod;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->ColumnHeadersVisible = false;
			this->dataGridView1->Location = System::Drawing::Point(136, 33);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(108, 113);
			this->dataGridView1->TabIndex = 9;
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToResizeColumns = false;
			this->dataGridView2->AllowUserToResizeRows = false;
			this->dataGridView2->BackgroundColor = System::Drawing::Color::Goldenrod;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->ColumnHeadersVisible = false;
			this->dataGridView2->Location = System::Drawing::Point(250, 33);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->Size = System::Drawing::Size(108, 113);
			this->dataGridView2->TabIndex = 12;
			// 
			// dataGridView3
			// 
			this->dataGridView3->AllowUserToResizeColumns = false;
			this->dataGridView3->AllowUserToResizeRows = false;
			this->dataGridView3->BackgroundColor = System::Drawing::Color::Goldenrod;
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->ColumnHeadersVisible = false;
			this->dataGridView3->Location = System::Drawing::Point(364, 33);
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->RowHeadersVisible = false;
			this->dataGridView3->Size = System::Drawing::Size(108, 113);
			this->dataGridView3->TabIndex = 13;
			// 
			// dataGridView4
			// 
			this->dataGridView4->AllowUserToResizeColumns = false;
			this->dataGridView4->AllowUserToResizeRows = false;
			this->dataGridView4->BackgroundColor = System::Drawing::Color::Goldenrod;
			this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView4->ColumnHeadersVisible = false;
			this->dataGridView4->Location = System::Drawing::Point(478, 33);
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->RowHeadersVisible = false;
			this->dataGridView4->Size = System::Drawing::Size(108, 113);
			this->dataGridView4->TabIndex = 14;
			// 
			// dataGridView5
			// 
			this->dataGridView5->AllowUserToResizeColumns = false;
			this->dataGridView5->AllowUserToResizeRows = false;
			this->dataGridView5->BackgroundColor = System::Drawing::Color::Goldenrod;
			this->dataGridView5->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView5->ColumnHeadersVisible = false;
			this->dataGridView5->Location = System::Drawing::Point(591, 33);
			this->dataGridView5->Name = L"dataGridView5";
			this->dataGridView5->RowHeadersVisible = false;
			this->dataGridView5->Size = System::Drawing::Size(108, 113);
			this->dataGridView5->TabIndex = 15;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(155, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 13);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Матрица A";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(269, 11);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 13);
			this->label2->TabIndex = 18;
			this->label2->Text = L"Матрица B";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(379, 11);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 13);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Матрица N1";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(497, 11);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(68, 13);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Матрица N2";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(614, 11);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(68, 13);
			this->label5->TabIndex = 21;
			this->label5->Text = L"Матрица N3";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(61, 57);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(42, 20);
			this->textBox1->TabIndex = 22;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(61, 80);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(42, 20);
			this->textBox2->TabIndex = 23;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(37, 57);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(23, 20);
			this->label6->TabIndex = 24;
			this->label6->Text = L"t0";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(42, 78);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(18, 20);
			this->label7->TabIndex = 25;
			this->label7->Text = L"T";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(10, 103);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(107, 20);
			this->label8->TabIndex = 26;
			this->label8->Text = L"Размер шага";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(28, 126);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(75, 20);
			this->textBox3->TabIndex = 27;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(5, 4);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(125, 20);
			this->label9->TabIndex = 28;
			this->label9->Text = L"Размер матриц";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(577, 600);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 24);
			this->button1->TabIndex = 29;
			this->button1->Text = L"Вычислить";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(26, 192);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox4->Size = System::Drawing::Size(112, 16);
			this->textBox4->TabIndex = 30;
			// 
			// dataGridView6
			// 
			this->dataGridView6->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView6->BackgroundColor = System::Drawing::Color::White;
			this->dataGridView6->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView6->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->dataGridView6->Location = System::Drawing::Point(0, 307);
			this->dataGridView6->Name = L"dataGridView6";
			this->dataGridView6->RowHeadersVisible = false;
			this->dataGridView6->Size = System::Drawing::Size(697, 134);
			this->dataGridView6->TabIndex = 31;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(697, 307);
			this->tabControl1->TabIndex = 11;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->chart1);
			this->tabPage1->Controls->Add(this->textBox4);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(689, 281);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"График";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// chart1
			// 
			chartArea1->AxisX->Interval = 0.5;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::Gray;
			chartArea1->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->Maximum = 10;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisY->Interval = 0.5;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gray;
			chartArea1->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisY->Maximum = 5;
			chartArea1->AxisY->Minimum = -5;
			chartArea1->CursorX->Interval = 0.001;
			chartArea1->CursorX->IsUserEnabled = true;
			chartArea1->CursorX->IsUserSelectionEnabled = true;
			chartArea1->CursorY->Interval = 0.001;
			chartArea1->CursorY->IsUserEnabled = true;
			chartArea1->CursorY->IsUserSelectionEnabled = true;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(3, 3);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			this->chart1->Size = System::Drawing::Size(683, 275);
			this->chart1->TabIndex = 10;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(3, 600);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(188, 20);
			this->label10->TabIndex = 32;
			this->label10->Text = L"Масштабирование по Y";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(196, 599);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(34, 24);
			this->button2->TabIndex = 33;
			this->button2->Text = L"+";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(237, 599);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(34, 24);
			this->button3->TabIndex = 34;
			this->button3->Text = L"-";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->tabControl1);
			this->panel1->Controls->Add(this->dataGridView6);
			this->panel1->Location = System::Drawing::Point(4, 153);
			this->panel1->Margin = System::Windows::Forms::Padding(2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(697, 441);
			this->panel1->TabIndex = 35;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->dataGridView4);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->comboBoxSize);
			this->panel2->Controls->Add(this->dataGridView1);
			this->panel2->Controls->Add(this->dataGridView2);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->dataGridView3);
			this->panel2->Controls->Add(this->textBox3);
			this->panel2->Controls->Add(this->dataGridView5);
			this->panel2->Controls->Add(this->label8);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->textBox2);
			this->panel2->Controls->Add(this->textBox1);
			this->panel2->Location = System::Drawing::Point(2, 2);
			this->panel2->Margin = System::Windows::Forms::Padding(2);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(708, 152);
			this->panel2->TabIndex = 36;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->panel2);
			this->panel3->Controls->Add(this->panel1);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Controls->Add(this->button1);
			this->panel3->Controls->Add(this->label10);
			this->panel3->Controls->Add(this->button2);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Margin = System::Windows::Forms::Padding(2);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(705, 630);
			this->panel3->TabIndex = 37;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::PaleGoldenrod;
			this->ClientSize = System::Drawing::Size(705, 630);
			this->Controls->Add(this->panel3);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResizeEnd += gcnew System::EventHandler(this, &MyForm::MyForm_ResizeEnd);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView6))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void comboBoxSize_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e)
	{
		dataGridView1->Rows->Clear();
		dataGridView1->Columns->Clear();
		dataGridView1->Columns->Add("", "");
		dataGridView2->Rows->Clear();
		dataGridView2->Columns->Clear();
		dataGridView2->Columns->Add("", "");
		dataGridView3->Rows->Clear();
		dataGridView3->Columns->Clear();
		dataGridView3->Columns->Add("", "");
		dataGridView4->Rows->Clear();
		dataGridView4->Columns->Clear();
		dataGridView4->Columns->Add("", "");
		dataGridView5->Rows->Clear();
		dataGridView5->Columns->Clear();
		dataGridView5->Columns->Add("", "");

		for (int i = 0; i < comboBoxSize->SelectedIndex; i++) {
			dataGridView1->Columns->Add("", "");
			dataGridView1->Rows->Add("", "");
			dataGridView2->Columns->Add("", "");
			dataGridView2->Rows->Add("", "");
			dataGridView3->Columns->Add("", "");
			dataGridView3->Rows->Add("", "");
			dataGridView4->Columns->Add("", "");
			dataGridView4->Rows->Add("", "");
			dataGridView5->Columns->Add("", "");
			dataGridView5->Rows->Add("", "");

		}
		dataGridView1->Rows->Add("", "");
		dataGridView2->Rows->Add("", "");
		dataGridView3->Rows->Add("", "");
		dataGridView4->Rows->Add("", "");
		dataGridView5->Rows->Add("", "");
		for (int i = 0; i < dataGridView1->RowCount; i++)
		{
			for (int j= 0; j < dataGridView1->ColumnCount; j++)
			{
				int init = 0;
				dataGridView1->Rows[i]->Cells[j]->Value = init;
				dataGridView3->Rows[i]->Cells[j]->Value = init;
				dataGridView5->Rows[i]->Cells[j]->Value = init;
				dataGridView4->Rows[i]->Cells[j]->Value = init;
				dataGridView2->Rows[i]->Cells[j]->Value = init;
			}
			
		}
		dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::DisplayedCells;
		dataGridView3->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::DisplayedCells;
		dataGridView2->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::DisplayedCells;
		dataGridView4->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::DisplayedCells;
		dataGridView5->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::DisplayedCells;
	}


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		QSMatrix<polynom>* A;
		QSMatrix<polynom>* B;
		//std::vector<polynom> B;
		QSMatrix<polynom>* N1;
		QSMatrix<polynom>* N2;
		QSMatrix<polynom>* N3;
		QSMatrix<double> *N3_real;
		int size;
		double t0;
		double T;
		double step;
		int cnt;
		try {
			size = dataGridView1->RowCount;
			t0 = Convert::ToDouble(textBox1->Text);
			T = Convert::ToDouble(textBox2->Text);
			step = Convert::ToDouble(textBox3->Text);
			cnt = (T - t0) / step;
			if (!cnt) throw "Err";
			A = new QSMatrix<polynom>(size, size, polynom());
			B = new QSMatrix<polynom>(size, size, polynom());
			N1 = new QSMatrix<polynom>(size, size, polynom());
			N2 = new QSMatrix<polynom>(size, size, polynom());
			N3 = new QSMatrix<polynom>(size, size, polynom());
			N3_real = new QSMatrix<double>(size, size, 0.0);
			for (int i = 0; i < dataGridView1->RowCount; i++)
			{
				for (int j = 0; j < dataGridView1->ColumnCount; j++)
				{
					(*A)(i, j) = polynom(Convert::ToDouble(dataGridView1->Rows[i]->Cells[j]->Value));
					(*B)(i, j) = polynom(Convert::ToDouble(dataGridView2->Rows[i]->Cells[j]->Value));
					(*N1)(i, j) = polynom(Convert::ToDouble(dataGridView3->Rows[i]->Cells[j]->Value));
					(*N2)(i, j) = polynom(Convert::ToDouble(dataGridView4->Rows[i]->Cells[j]->Value));
					(*N3)(i, j) = polynom(Convert::ToDouble(dataGridView5->Rows[i]->Cells[j]->Value));
					(*N3_real)(i, j) = Convert::ToDouble(dataGridView5->Rows[i]->Cells[j]->Value);
				}
				//B.emplace_back(polynom(Convert::ToDouble(dataGridView2->Rows[i]->Cells[0]->Value)));
			}
		}
		catch (...)
		{
			MessageBox::Show("Incorrect input", "Error", MessageBoxButtons::OK);
			return;
		}
		if (N3_real->Det() == 0) {
			MessageBox::Show("Zero determinant", "Error", MessageBoxButtons::OK);
			return;
		}
		while (chart1->Series->Count > 0)
		{
			chart1->Series->Remove(chart1->Series[0]);
		}
		
		dataGridView6->Rows->Clear();
		dataGridView6->Columns->Clear();
		dataGridView6->Columns->Add("t", "t");
		dataGridView6->Columns->Add("U(t)", "U(t)");
		for (int i = 0; i < size* 2 -1; i++)
			dataGridView6->Columns->Add("P" + (i + 1).ToString() + "(t)", "P" + (i + 1).ToString() + "(t)");
		for (int i = 0; i < size; i++)
			dataGridView6->Columns->Add("X" + (i + 1).ToString() + "(t)", "X" + (i + 1).ToString() + "(t)");
		
		chart1->ChartAreas[0]->AxisX->Interval = (T - t0) / 20;
		chart1->ChartAreas[0]->AxisX->Maximum = T;
		chart1->ChartAreas[0]->AxisX->Minimum = t0;
		

		
		textBox4->Text = "";
		QSMatrix<polynom> P(size, size, polynom());
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				P(i, j) = polynom(i + j);

		QSMatrix<polynom> dPdt(size, size, polynom(0.0));
		dPdt = P * (*B) * (*N3) * (*B).transpose() * P - ((*A).transpose() *P + P * (*A) + (*N2));
		//auto sys_p = get_syste(dPdt);
		std::vector<std::function<double(const std::vector<double>&)>> sys_p;
		for (int i = 0; i < dPdt.get_rows(); i++) {
			sys_p.emplace_back(dPdt(0, i).gen_getVal());
		}
		for (int i = 1; i < dPdt.get_cols(); i++) {
			sys_p.emplace_back(dPdt(i, dPdt.get_rows() - 1).gen_getVal());
		}
		for (int i = 0; i<dPdt.get_rows(); i++) {
			for (int j = 0; j<dPdt.get_cols(); j++) {
				String^ s = gcnew String(dPdt(i, j).toString().c_str());
				textBox4->Text += s + ", ";
			}
			textBox4->Text += "\r\n";
		}

		std::vector<double> p_curr; //начальные условия, в дальнейшем текущие
		for (int i = 0; i < (*N1).get_rows(); i++) {
			p_curr.push_back((*N1)(0, i).getVal({ 1,1,1,1,1 }));
		}
		for (int i = 1; i < (*N1).get_cols(); i++) {
			p_curr.push_back((*N1)(i, (*N1).get_rows() - 1).getVal({ 1,1,1,1,1 }));
		}
		//textBox4->Text = "";
		std::vector<QSMatrix<polynom>> PotT;	
		std::vector<std::vector<double>> Pvals;
		for (double t = T; t > t0 - step; t-=step)
		{
			auto res_ot_t = runge(step, sys_p, p_curr, -1);
			QSMatrix<polynom> tmp_matr(size, size, polynom());
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					tmp_matr(i, j) = res_ot_t[i + j];
				}
			}
			dataGridView6->Rows->Add("", "");				
				
		//	textBox4->Text += res_ot_t[0] + "\r\n";
			PotT.emplace_back(tmp_matr);
			p_curr = res_ot_t;
			Pvals.emplace_back(res_ot_t);
		}

		double t_0 = t0;
		for (int i = 0; i < Pvals.size(); i++)
		{			
			int k = Pvals.size() - i - 1;
			dataGridView6->Rows[i]->Cells[0]->Value = roundf(t_0 * 100) / 100;
			t_0 += step;
			for (int j = 0; j < Pvals[k].size(); j++)
				dataGridView6->Rows[i]->Cells[j + 2]->Value = Pvals[k][j];
		}

		std::vector<polynom> UotT; // U от времени
		auto revers = N3_real->getReversed(); //Получаем n3^-1
		QSMatrix<polynom> minusN3rev(size, size, polynom());
		for (int i = 0; i<revers.get_rows(); i++) {
			for (int j = 0; j<revers.get_cols(); j++) {
				minusN3rev(i, j) = polynom((-1) * revers(i, j));
			}
		}
		//QSMatrix<polynom> Um(size, size, polynom(0.0));
		QSMatrix<polynom> X(size, size, polynom());
		for (int i = 0; i < size; i++) {
			X(i, 0) = polynom(i);
		}

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				String^ s = gcnew String(minusN3rev(i, j).toString().c_str());
				textBox4->Text += s + ", ";
			}
			textBox4->Text += "\r\n";
		}

		std::vector<double> x_curr(size,1.0); //начальные условия, в дальнейшем текущие
		
		//Um = minusN3rev * (*B).transpose() * PotT[0] * X;
		std::vector<std::vector<double>> XotT;
		double t = 0;
		for (int i = 0; i < PotT.size(); t += step, i++)
		{
			QSMatrix<polynom> U_tmp(size, size, polynom());
			U_tmp = minusN3rev * (*B).transpose() * PotT[i] * X;
			UotT.push_back(U_tmp(0, 0));			
			QSMatrix<polynom> dXDt(size, size, polynom());
			dXDt = (*A) * X + (*B) * U_tmp;
			/*for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					String^ s = gcnew String(dXDt(i, j).toString().c_str());
					textBox4->Text += s + ", ";
				}
				textBox4->Text += "\r\n";
			}*/
			std::vector<std::function<double(const std::vector<double>&)>> sys_x;
			for (int k = 0; k < size; k++)
				sys_x.emplace_back(dXDt(k, 0).gen_getVal());
			XotT.emplace_back(runge(step, sys_x, x_curr, 1));
			x_curr = XotT[XotT.size() - 1];
			
			textBox4->Text += U_tmp(0, 0).getVal(x_curr) + "\r\n";
		}

		for (int i = 0; i < XotT.size(); i++)
		{
			for (int j = 0; j < XotT[i].size(); j++)
			{
				dataGridView6->Rows[i]->Cells[j + 1 + size * 2]->Value = XotT[i][j];				
			}
			dataGridView6->Rows[i]->Cells[1]->Value = UotT[i].getVal(XotT[i]);
				
		}

	
		//
 
		int pcol = 255;
		int xcol = 255;
		int offs = 20;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 255);
		for (int i = 1, z = 0; i < dataGridView6->ColumnCount; i++)
		{
			//if (!dataGridView6->Columns[i]->HeaderText->Contains("P")) {
				chart1->Series->Add(dataGridView6->Columns[i]->HeaderText);
				chart1->Series[z]->ChartType = DataVisualization::Charting::SeriesChartType::Spline;
				for (int k = 0; k < dataGridView6->RowCount - 1; k++)
				{
					chart1->Series[z]->Points->AddXY(dataGridView6->Rows[k]->Cells[0]->Value, dataGridView6->Rows[k]->Cells[i]->Value);
				}
				if (dataGridView6->Columns[i]->HeaderText->Contains("P")) {
					//chart1->Series[z]->Color = Color::FromArgb(100 + rand() % 20, 100 + rand() % 20, pcol);
					chart1->Series[z]->Color = Color::FromArgb(dis(gen), dis(gen), dis(gen));
					pcol -= offs;
				}
				else if (dataGridView6->Columns[i]->HeaderText->Contains("X")) {
					//chart1->Series[z]->Color = Color::FromArgb(xcol, 100 + rand() % 20, 100 + rand() % 20);
					chart1->Series[z]->Color = Color::FromArgb(dis(gen), dis(gen), dis(gen));
					xcol -= offs;
				}
				else if (dataGridView6->Columns[i]->HeaderText->Contains("U")) chart1->Series[z]->Color = Color::Black;
				z++;
			//}
		}

		
		
		//chart1->Series["P(t)"]->Points->AddXY(t, res_ot_t[0]);
		//chart1->Series["X(t)"]->Points->AddXY(t, x_curr[0]);
		//chart1->Series["U(t)"]->Points->AddXY(t, U_tmp(0, 0).getVal(x_curr));

		//polynom U
		
		
		chart1->ChartAreas[0]->AxisY->Interval = step * 10;
		chart1->ChartAreas[0]->AxisY->Maximum = 1;
		chart1->ChartAreas[0]->AxisY->Minimum = -1;
		chart1->ChartAreas[0]->AxisY->Interval = 6.0 / 10.0;
	}
	
	double cachemin = 0.0;
	double cachemax = 0.0;
	bool isfirst = true;
	const double max(double a, double b)
	{
		return (abs(a) < abs(b)) ? b : a;
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!isfirst) {
		chart1->ChartAreas[0]->AxisY->Maximum = Math::Round(max(chart1->ChartAreas[0]->AxisY->Maximum * 0.9, cachemax));
		chart1->ChartAreas[0]->AxisY->Minimum = Math::Round(max(chart1->ChartAreas[0]->AxisY->Minimum * 0.9, cachemin));
		double inter = abs(chart1->ChartAreas[0]->AxisY->Minimum - chart1->ChartAreas[0]->AxisY->Maximum) / 10;
		chart1->ChartAreas[0]->AxisY->Interval = roundf(inter * 100) / 100;
	}
}		
		
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	if (isfirst)
	{
		cachemax = chart1->ChartAreas[0]->AxisY->Maximum;
		cachemin = chart1->ChartAreas[0]->AxisY->Minimum;
		isfirst = false;
	}
	chart1->ChartAreas[0]->AxisY->Maximum = Math::Round(chart1->ChartAreas[0]->AxisY->Maximum * 1.2, 1);
	chart1->ChartAreas[0]->AxisY->Minimum = Math::Round(chart1->ChartAreas[0]->AxisY->Minimum * 1.2, 1);
	chart1->ChartAreas[0]->AxisY->Interval = Math::Round(abs(chart1->ChartAreas[0]->AxisY->Minimum - chart1->ChartAreas[0]->AxisY->Maximum) / 10.0, 2);
}

private: System::Void MyForm_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {
	//panel1->Width = panel3->Width - panel2->Width;
}
private: System::Void MyForm_Resize(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	
}
};
}
