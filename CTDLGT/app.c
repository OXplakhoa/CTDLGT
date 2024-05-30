#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc dữ liệu cho Người thuê
typedef struct {
    int id;
    char name[100];
    char phone[15];
    char email[100];
} NguoiThue;

// Cấu trúc dữ liệu cho Phòng trọ
typedef struct {
    int id;
    char name[100];
    int maxPeople;
    int currentPeople;
    int rentPrice;
} PhongTro;

// Cấu trúc dữ liệu cho Hóa đơn
typedef struct {
    int id;
    int renterId;
    char date[20];
    float totalAmount;
} HoaDon;

// Cấu trúc dữ liệu cho Chi tiết hóa đơn
typedef struct {
    int invoiceId;
    int roomId;
    char month[10];
    float amount;
} ChiTietHoaDon;

// Node cho BST của người thuê
typedef struct Node {
    NguoiThue data;
    struct Node *left;
    struct Node *right;
} Node;

// Node cho BST của phòng trọ
typedef struct PhongTroNode {
    PhongTro data;
    struct PhongTroNode* left;
    struct PhongTroNode* right;
} PhongTroNode;

// Node cho BST của hóa đơn
typedef struct HoaDonNode {
    HoaDon data;
    struct HoaDonNode* left;
    struct HoaDonNode* right;
} HoaDonNode;

// Node cho BST của chi tiết hóa đơn
typedef struct ChiTietHoaDonNode {
    ChiTietHoaDon data;
    struct ChiTietHoaDonNode* left;
    struct ChiTietHoaDonNode* right;
} ChiTietHoaDonNode;

// Hàm tạo node mới và thêm node cho BST của người thuê
Node* createNode(NguoiThue data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, NguoiThue data) {
    if (root == NULL) return createNode(data);

    if (data.id < root->data.id)
        root->left = insertNode(root->left, data);
    else if (data.id > root->data.id)
        root->right = insertNode(root->right, data);

    return root;
}

// Hàm tạo node và thêm node vào BST của phòng trọ
PhongTroNode* taoPhongTroNode(PhongTro data) {
    PhongTroNode *newNode = (PhongTroNode*)malloc(sizeof(PhongTroNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

PhongTroNode* themPhongTroNode(PhongTroNode* root, PhongTro data) {
    if (root == NULL) return taoPhongTroNode(data);

    if (data.id < root->data.id)
        root->left = themPhongTroNode(root->left, data);
    else if (data.id > root->data.id)
        root->right = themPhongTroNode(root->right, data);
    return root;
}

// Hàm tạo node và thêm node vào BST của hóa đơn
HoaDonNode* taoHoaDonNode(HoaDon data) {
    HoaDonNode *newNode = (HoaDonNode*)malloc(sizeof(HoaDonNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

HoaDonNode* themHoaDonNode(HoaDonNode* root, HoaDon data) {
    if (root == NULL) return taoHoaDonNode(data);

    if (data.id < root->data.id)
        root->left = themHoaDonNode(root->left, data);
    else if (data.id > root->data.id)
        root->right = themHoaDonNode(root->right, data);
    return root;
}

// Hàm tạo node và thêm Node vào BST của chi tiết hóa đơn
ChiTietHoaDonNode* taoCTHoaDonNode(ChiTietHoaDon data) {
    ChiTietHoaDonNode *newNode = (ChiTietHoaDonNode*)malloc(sizeof(ChiTietHoaDonNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

ChiTietHoaDonNode* themCTHoaDonNode(ChiTietHoaDonNode* root, ChiTietHoaDon data) {
    if (root == NULL) return taoCTHoaDonNode(data);

    if (data.invoiceId < root->data.invoiceId)
        root->left = themCTHoaDonNode(root->left, data);
    else if (data.invoiceId > root->data.invoiceId)
        root->right = themCTHoaDonNode(root->right, data);
    return root;
}

// Hàm tìm kiếm trong BST
Node* searchNode(Node* root, int id) {
    if (root == NULL || root->data.id == id)
        return root;

    if (id < root->data.id)
        return searchNode(root->left, id);
    
    return searchNode(root->right, id);
}

// Hàm đọc dữ liệu và in từ file Người thuê
void readNguoiThue(const char *filename, Node **root) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (count == 0) { // Bỏ qua dòng tiêu đề
            count++;
            continue;
        }
        NguoiThue nguoiThue;
        sscanf(line, "%d,%[^,],%[^,],%s", &nguoiThue.id, nguoiThue.name, nguoiThue.phone, nguoiThue.email);
        *root = insertNode(*root, nguoiThue);
        count++;
    }
    fclose(file);
}

void printNguoiThueInOrder(Node* root) {
    if (root != NULL) {
        printNguoiThueInOrder(root->left);
        printf("ID: %d, Ten: %s, So dien thoai: %s, Email: %s\n", 
               root->data.id, root->data.name, root->data.phone, root->data.email);
        printNguoiThueInOrder(root->right);
    }
}

// Hàm đọc dữ liệu và in từ file Phòng Trọ
void readPhongTro(const char *filename, PhongTroNode **root) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (count == 0) {
            count++;
            continue;
        }
        PhongTro phongTro;
        sscanf(line, "%d,%[^,],%d,%d,%d", &phongTro.id, phongTro.name, &phongTro.maxPeople, &phongTro.currentPeople, &phongTro.rentPrice);
        *root = themPhongTroNode(*root, phongTro);
        count++;
    }
    fclose(file);
}

void printPhongTroInOrder(PhongTroNode* root) {
    if (root != NULL) {
        printPhongTroInOrder(root->left);
        printf("ID: %d, Ten phong: %s, So nguoi toi da: %d, So nguoi hien tai: %d, Gia thue: %d\n", 
                root->data.id, root->data.name, root->data.maxPeople, root->data.currentPeople, root->data.rentPrice);
        printPhongTroInOrder(root->right);
    }
}

// Hàm đọc dữ liệu và in từ file Hóa Đơn
void readHoaDon(const char *filename, HoaDonNode **root) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (count == 0) {
            count++;
            continue;
        }
        HoaDon hoaDon;
        sscanf(line, "%d,%d,%[^,],%f", &hoaDon.id, &hoaDon.renterId, hoaDon.date, &hoaDon.totalAmount);
        *root = themHoaDonNode(*root, hoaDon);
        count++;
    }
    fclose(file);
}


//-----------------------------------------------------------------------
void printHoaDonInOrder(HoaDonNode* root) {
    if (root != NULL) {
        printHoaDonInOrder(root->left);
        printf("ID Hoa don: %d, ID Nguoi thue: %d, Ngay thang: %s, Tong tien: %.2f\n", 
               root->data.id, root->data.renterId, root->data.date, root->data.totalAmount);
        printHoaDonInOrder(root->right);
    }
}

//Hàm đọc dữ liệu từ file và in chi tiết hóa đơn
void readCTHoaDon(const char *filename,Node **root){
    FILE *file = fopen(filename,"r");
    if (file == NULL){
        printf("Khong the mo file %s\n",filename);
        return;
    }

    char line[256];
    int c = 0;
    while(fgets(line,sizeof(line),file)){
        if (c == 0){
            c++;
            continue;
        }
        ChiTietHoaDon CTHoaDon;
        sscanf("%d,%d,%[^,],%d",&CTHoaDon.invoiceId,&CTHoaDon.roomId,CTHoaDon.month,CTHoaDon.amount);
        *root = themCTHoaDonNode(*root,CTHoaDon);
        c++;
    }
    fclose(file);
}
void printChiTietHoaDonInOrder(ChiTietHoaDonNode* root) {
    if (root != NULL) {
        printChiTietHoaDonInOrder(root->left);
        printf("ID Hoa don: %d, ID Phong: %d, Thang: %s, So tien: %.2f\n", 
               root->data.invoiceId, root->data.roomId, root->data.month, root->data.amount);
        printChiTietHoaDonInOrder(root->right);
    }
}

// Hàm ghi dữ liệu Người thuê vào file
void writeNguoiThue(const char *filename, Node *root) {
    if (root == NULL) return;

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "%d,%s,%s,%s\n", root->data.id, root->data.name, root->data.phone, root->data.email);

    writeNguoiThue(filename, root->left);
    writeNguoiThue(filename, root->right);

    fclose(file);
}

// Hàm thêm thông tin phòng trọ mới (lưu vào file)
void addPhongTro(const char *filename, PhongTro phongTro) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "%d,%s,%d,%d,%d\n", phongTro.id, phongTro.name, phongTro.maxPeople, phongTro.currentPeople, phongTro.rentPrice);
    fclose(file);
}

// Hàm thêm thông tin hóa đơn mới (lưu vào file)
void addHoaDon(const char *filename, HoaDon hoaDon) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "%d,%d,%s,%.2f\n", hoaDon.id, hoaDon.renterId, hoaDon.date, hoaDon.totalAmount);
    fclose(file);
}

// Hàm thêm thông tin chi tiết hóa đơn mới (lưu vào file)
void addChiTietHoaDon(const char *filename, ChiTietHoaDon ctHoaDon) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "%d,%d,%s,%.2f\n", ctHoaDon.invoiceId, ctHoaDon.roomId, ctHoaDon.month, ctHoaDon.amount);
    fclose(file);
}

// Hàm in thông tin Người thuê từ BST
void printInOrder(Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d, %s, %s, %s\n", root->data.id, root->data.name, root->data.phone, root->data.email);
        printInOrder(root->right);
    }
}

// Hàm nhập thông tin Người thuê
NguoiThue inputNguoiThue() {
    NguoiThue nguoiThue;
    printf("Nhap ID: ");
    scanf("%d", &nguoiThue.id);
    printf("Nhap Ten: ");
    scanf(" %[^\n]s", nguoiThue.name);
    printf("Nhap So dien thoai: ");
    scanf(" %[^\n]s", nguoiThue.phone);
    printf("Nhap Email: ");
    scanf(" %[^\n]s", nguoiThue.email);
    return nguoiThue;
}

// Hàm nhập thông tin Phòng trọ
PhongTro inputPhongTro() {
    PhongTro phongTro;
    printf("Nhap ID phong: ");
    scanf("%d", &phongTro.id);
    printf("Nhap Ten phong: ");
    scanf(" %[^\n]s", phongTro.name);
    printf("Nhap So nguoi toi da: ");
    scanf("%d", &phongTro.maxPeople);
    printf("Nhap So nguoi hien tai: ");
    scanf("%d", &phongTro.currentPeople);
    printf("Nhap Gia thue: ");
    scanf("%d", &phongTro.rentPrice);
    return phongTro;
}

// Hàm nhập thông tin Hóa đơn
HoaDon inputHoaDon() {
    HoaDon hoaDon;
    printf("Nhap ID hoa don: ");
    scanf("%d", &hoaDon.id);
    printf("Nhap ID nguoi thue: ");
    scanf("%d", &hoaDon.renterId);
    printf("Nhap Ngay thang: ");
    scanf(" %[^\n]s", hoaDon.date);
    printf("Nhap Tong tien: ");
    scanf("%f", &hoaDon.totalAmount);
    return hoaDon;
}

// Hàm nhập thông tin Chi tiết hóa đơn
ChiTietHoaDon inputChiTietHoaDon() {
    ChiTietHoaDon ctHoaDon;
    printf("Nhap ID hoa don: ");
    scanf("%d", &ctHoaDon.invoiceId);
    printf("Nhap ID phong: ");
    scanf("%d", &ctHoaDon.roomId);
    printf("Nhap Thang: ");
    scanf(" %[^\n]s", ctHoaDon.month);
    printf("Nhap So tien: ");
    scanf("%f", &ctHoaDon.amount);
    return ctHoaDon;
}

// Hàm hiển thị menu
void showMenu() {
    printf("0. In thong tin\n");
    printf("1. Them Nguoi thue\n");
    printf("2. Them Phong tro\n");
    printf("3. Them Hoa don\n");
    printf("4. Them Chi tiet hoa don\n");
    printf("5. Thoat\n");
}

int main() {
    Node *nguoiThueRoot = NULL;
    PhongTroNode *phongTroRoot = NULL;
    HoaDonNode *hoaDonRoot = NULL;
    ChiTietHoaDonNode *chiTietHoaDonRoot = NULL;

    // Đọc dữ liệu từ file
    readNguoiThue("nguoi_thue.txt", &nguoiThueRoot);
    readPhongTro("phong_tro.txt", &phongTroRoot);
    readHoaDon("hoa_don.txt", &hoaDonRoot);
    readCTHoaDon("ct_hoa_don.txt", &chiTietHoaDonRoot);

    int choice;
    while (1) {
        showMenu();
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        if (choice == 5) break;

        switch (choice) {
            case 0: {
                printf("Danh sach nguoi thue:\n");
                printNguoiThueInOrder(nguoiThueRoot);
                printf("\nDanh sach phong tro:\n");
                printPhongTroInOrder(phongTroRoot);
                printf("\nDanh sach hoa don:\n");
                printHoaDonInOrder(hoaDonRoot);
                printf("\nDanh sach chi tiet hoa don:\n");
                printChiTietHoaDonInOrder(chiTietHoaDonRoot);
                break;
            }
            case 1: {
                NguoiThue nguoiThue = inputNguoiThue();
                nguoiThueRoot = insertNode(nguoiThueRoot, nguoiThue);
                writeNguoiThue("nguoi_thue.txt", nguoiThueRoot);
                break;
            }
            case 2: {
                PhongTro phongTro = inputPhongTro();
                addPhongTro("phong_tro.txt", phongTro);
                break;
            }
            case 3: {
                HoaDon hoaDon = inputHoaDon();
                addHoaDon("hoa_don.txt", hoaDon);
                break;
            }
            case 4: {
                ChiTietHoaDon ctHoaDon = inputChiTietHoaDon();
                addChiTietHoaDon("ct_hoa_don.txt", ctHoaDon);
                break;
            }
            default:
                printf("Lua chon khong hop le!\n");
        }
    }

    return 0;
}
