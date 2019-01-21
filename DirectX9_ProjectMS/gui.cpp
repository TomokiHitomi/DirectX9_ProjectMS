//=============================================================================
//
// GUI���� [gui.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
// �f�o�b�O�p
#ifdef _DEBUG
#include "main.h"
#include "gui.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GUI_FONT ("resources\\fonts\\GenShinGothic\\GenShinGothic-P-Normal.ttf")
#define GUI_FONT_SIZE (15.0f * SCREEN_SCALE)
#define GUI_FONT_POS (20 * SCREEN_SCALE)

#define GUI_FPS_ALERT_1 (60)
#define GUI_FPS_ALERT_2 (55)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool Gui::s_bUse = true;

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
Gui::Gui(void)
{
}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
Gui::~Gui(void)
{
	//Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void Gui::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	// imgui�̏���������
	ImGui::CreateContext();
	ImGui_ImplDX9_Init(hWnd, pDevice);

	//// �X�^�C�����w��i���j
	//ImGui::StyleColorsDark();

	// I/O��������
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF(
		GUI_FONT,
		GUI_FONT_SIZE,
		NULL,
		io.Fonts->GetGlyphRangesJapanese()
	);
}

//=============================================================================
// �X�V����
//=============================================================================
void Gui::Uninit(void)
{
	// imgui�̉��
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
}

//=============================================================================
// �X�V�J�n����
//=============================================================================
void Gui::Start(void)
{
	// �V�K�t���[�����쐬
	ImGui_ImplDX9_NewFrame();

	// FPS�̎擾
	int nFps = GetFps();

	// FPS�̒l���w��l���㉺�Ń^�C�g���̐F��ύX
	if (nFps >= GUI_FPS_ALERT_1)
	{	// �O���[��
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.2f, 0.7f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.2f, 0.7f, 0.2f, 0.5f));
	}
	else if (nFps >= GUI_FPS_ALERT_2)
	{	// �C�G���[
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.7f, 0.7f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.7f, 0.7f, 0.2f, 0.5f));
	}
	else
	{	// ���b�h
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.7f, 0.2f, 0.2f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.7f, 0.2f, 0.2f, 0.5f));
	}

	// �E�B���h�E�F�����i�������j�ɐݒ�
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.4f));
	// �E�B���h�E�̏����ʒu��ݒ�
	ImGui::SetNextWindowPos(ImVec2(GUI_FONT_POS, GUI_FONT_POS), ImGuiSetCond_Once);
	//ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

	// imgui�̍X�V�J�n
	ImGui::Begin("Debug");

	// FPS��\��
	ImGui::Text("FPS [%d]\n", nFps);
}

//=============================================================================
// �X�V�I������
//=============================================================================
void Gui::End(void)
{
	// imgui�̍X�V�I��
	ImGui::End();

	// �ύX�����X�^�C���̐������|�b�v
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Gui::Draw(void)
{
	// imgui�̕`��
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
#endif