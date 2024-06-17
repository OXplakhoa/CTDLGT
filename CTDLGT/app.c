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
        printf("Khong the mo file %s\n", filename);
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
    int c = 0;
    while (fgets(line, sizeof(line), file)) {
        if (c == 0) {
            c++;
            continue;
        }
        PhongTro phongTro;
        sscanf(line, "%d,%[^,],%d,%d,%d", &phongTro.id, phongTro.name, &phongTro.maxPeople, &phongTro.currentPeople, &phongTro.rentPrice);
        *root = themPhongTroNode(*root, phongTro);
        c++;
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
    int c = 0;
    while (fgets(line, sizeof(line), file)) {
        if (c == 0) {
            c++;
            continue;
        }
        HoaDon hoaDon;
        sscanf(line, "%d,%d,%[^,],%f", &hoaDon.id, &hoaDon.renterId, hoaDon.date, &hoaDon.totalAmount);
        *root = themHoaDonNode(*root, hoaDon);
        c++;
    }
    fclose(file);
}

void printHoaDonInOrder(HoaDonNode* root) {
    if (root != NULL) {
        printHoaDonInOrder(root->left);
        printf("ID Hoa don: %d, ID Nguoi thue: %d, Ngay thang: %s, Tong tien: %.2f\n", 
               root->data.id, root->data.renterId, root->data.date, root->data.totalAmount);
        printHoaDonInOrder(root->right);
    }
}

// Hàm đọc dữ liệu và in từ file Chi tiết Hóa Đơn
void readChiTietHoaDon(const char *filename, ChiTietHoaDonNode **root) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    char line[256];
    int c = 0;
    while (fgets(line, sizeof(line), file)) {
        if (c == 0) {
            c++;
            continue;
        }
        ChiTietHoaDon chiTietHoaDon;
        sscanf(line, "%d,%d,%[^,],%f", &chiTietHoaDon.invoiceId, &chiTietHoaDon.roomId, chiTietHoaDon.month, &chiTietHoaDon.amount);
        *root = themCTHoaDonNode(*root, chiTietHoaDon);
        c++;
    }
    fclose(file);
}

void printChiTietHoaDonInOrder(ChiTietHoaDonNode* root) {
    if (root != NULL) {
        printChiTietHoaDonInOrder(root->left);
        printf("ID Hoa don: %d, ID Phong tro: %d, Thang: %s, So tien: %.2f\n", 
               root->data.invoiceId, root->data.roomId, root->data.month, root->data.amount);
        printChiTietHoaDonInOrder(root->right);
    }
}

// Các hàm ghi dữ liệu vào file
void writeNguoiThueNode(FILE *file, Node *root) {
    if (root != NULL) {
        writeNguoiThueNode(file, root->left);
        fprintf(file, "%d,%s,%s,%s\n", root->data.id, root->data.name, root->data.phone, root->data.email);
        writeNguoiThueNode(file, root->right);
    }
}

void writeNguoiThue(const char *filename, Node *root) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }
    fprintf(file, "ID,Name,Phone,Email\n");
    writeNguoiThueNode(file, root);
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
// Hàm so sánh Hóa đơn theo tổng tiền giảm dần
int compareHoaDon(const void* a, const void* b) {
    HoaDon* hoaDonA = (HoaDon*)a;
    HoaDon* hoaDonB = (HoaDon*)b;
    return (hoaDonB->totalAmount - hoaDonA->totalAmount);
}
// Hàm so sánh Hóa đơn theo tên người thuê và mã người thuê
int compareHoaDonByRenterName(const void* a, const void* b, void* nguoiThueTree) {
    HoaDon* hoaDonA = (HoaDon*)a;
    HoaDon* hoaDonB = (HoaDon*)b;

    // Tìm người thuê tương ứng với mỗi hóa đơn
    Node* renterA = searchNode((Node*)nguoiThueTree, hoaDonA->renterId);
    Node* renterB = searchNode((Node*)nguoiThueTree, hoaDonB->renterId);

    // So sánh tên người thuê
    int cmp = strcmp(renterA->data.name, renterB->data.name);
    if (cmp != 0)
        return cmp;

    // Nếu tên giống nhau, so sánh theo mã người thuê
    return hoaDonA->renterId - hoaDonB->renterId;
}

// Hàm sắp xếp và in danh sách Hóa đơn giảm dần theo tổng tiền
void printHoaDonSortedByTotalAmount(HoaDonNode* root) {
    // Tạo mảng động để chứa các Hóa đơn
    HoaDon* invoices = (HoaDon*)malloc(sizeof(HoaDon) * 100);
    int count = 0;

    // Duyệt cây và thêm các hóa đơn vào mảng
    HoaDonNode* stack[100];
    int top = -1;
    HoaDonNode* current = root;
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        invoices[count++] = current->data;
        current = current->right;
    }

    // Sắp xếp mảng theo tổng tiền giảm dần
    qsort(invoices, count, sizeof(HoaDon), compareHoaDon);

    // In danh sách Hóa đơn đã sắp xếp
    for (int i = 0; i < count; i++) {
        printf("ID Hoa Don: %d, ID Nguoi Thue: %d, Ngay Lap: %s, Tong Tien: %.2f\n",
            invoices[i].id, invoices[i].renterId, invoices[i].date, invoices[i].totalAmount);
    }

    // Giải phóng bộ nhớ
    free(invoices);
}
// Hàm sắp xếp và in danh sách Hóa đơn tăng dần theo tên người thuê và mã người thuê
void printHoaDonSortedByRenterName(HoaDonNode* root, Node* nguoiThueTree) {
    // Tạo mảng động để chứa các Hóa đơn
    HoaDon* invoices = (HoaDon*)malloc(sizeof(HoaDon) * 100);
    int count = 0;

    // Duyệt cây và thêm các hóa đơn vào mảng
    HoaDonNode* stack[100];
    int top = -1;
    HoaDonNode* current = root;
    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        invoices[count++] = current->data;
        current = current->right;
    }

    // Sắp xếp mảng theo tên người thuê và mã người thuê
    //qsort_s(invoices, count, sizeof(HoaDon), compareHoaDonByRenterName, nguoiThueTree);

    // In danh sách Hóa đơn đã sắp xếp
    for (int i = 0; i < count; i++) {
        Node* renter = searchNode(nguoiThueTree, invoices[i].renterId);
        printf("ID Hoa Don: %d, ID Nguoi Thue: %d, Ten Nguoi Thue: %s, Ngay Lap: %s, Tong Tien: %.2f\n",
            invoices[i].id, invoices[i].renterId, renter->data.name, invoices[i].date, invoices[i].totalAmount);
    }

    // Giải phóng bộ nhớ
    free(invoices);
}
// Hàm tìm số người ở nhiều nhất
void maxpeople(PhongTroNode *root,int m){
    if(root!=NULL)
    {
    maxpeople(root->left,m);
    if(root->data.currentPeople>m)
    m=root->data.currentPeople;
    maxpeople(root->right,m);
    }
}

// Hàm xuất phòng có người ở nhiểu nhất
void Printmaxpeople(PhongTroNode*root,int m)
{
    if(root!=NULL)
    {
    Printmaxpeople(root->left,m);
    if(root->data.currentPeople==m)
    printf("ID: %d, Ten phong: %s, So nguoi toi da: %d, So nguoi hien tai: %d, Gia thue: %d\n",root->data.id, root->data.name, root->data.maxPeople, root->data.currentPeople, root->data.rentPrice);
    Printmaxpeople(root->right,m);
    }
}

// Hàm xuất thông tin hóa đơn và chi tiết hóa đơn khi biết mã hóa đơn
void printHoadon(HoaDonNode *root, int mahoadon)
{
    if(root!=NULL)
    {
        printHoadon(root->left,mahoadon);
        if(root->data.id==mahoadon)
            printf("ID Hoa don: %d, ID Nguoi thue: %d, Ngay thang: %s, Tong tien: %.2f\n",root->data.id, root->data.renterId, root->data.date, root->data.totalAmount);
        printHoadon(root->right,mahoadon);
    }
}
void printChitietHoadon(ChiTietHoaDonNode *root, int mahoadon)
{
    if(root!=NULL)
    {
        printChitietHoadon(root->left,mahoadon);
        if(root->data.invoiceId==mahoadon)
        printf("ID Hoa don: %d, ID Phong: %d, Thang: %s, So tien: %.2f\n",root->data.invoiceId, root->data.roomId, root->data.month, root->data.amount);
        printChitietHoadon(root->right,mahoadon);
    }
}
// Liệt kê danh sách chi tiết các hóa đơn khi biết mã khách hàng
void lietKeChiTietHoaDon(Node* renterRoot, HoaDonNode* hoaDonRoot, ChiTietHoaDonNode* chiTietHoaDonRoot, int renterId) {
    // Tìm khách hàng trong danh sách khách hàng
    Node* renter = searchNode(renterRoot, renterId);
    if (renter == NULL) {
        printf("Khong tim thay khach hang voi ID: %d\n", renterId);
        return;
    }

    // In ra thông tin khách hàng đã tìm thấy
    printf("Chi tiet hoa don cho khach hang: %s\n", renter->data.name);

    // Tìm và liệt kê các hóa đơn của khách hàng
    HoaDonNode* hoaDon = hoaDonRoot;
    while (hoaDon != NULL) {
        printf("Hoa don ID: %d, Ngay: %s, Tong so tien: %.2f\n", 
                hoaDon->data.id, hoaDon->data.date, hoaDon->data.totalAmount);

        // Tìm và liệt kê các chi tiết hóa đơn của từng hóa đơn
        ChiTietHoaDonNode* chiTiet = chiTietHoaDonRoot;
        while (chiTiet != NULL) {
            if (chiTiet->data.invoiceId == hoaDon->data.id) {
                printf("   Phong ID: %d, Thang: %s, So tien: %.2f\n", 
                        chiTiet->data.roomId, chiTiet->data.month, chiTiet->data.amount);
            }

            // Di chuyển con trỏ chiTiet sang node tiếp theo
            if (chiTiet->data.invoiceId < hoaDon->data.id) {
                chiTiet = chiTiet->right;
            } else {
                chiTiet = chiTiet->left;
            }
        }

        // Di chuyển con trỏ hoaDon sang node tiếp theo
        if (hoaDon->data.renterId < renterId) {
            hoaDon = hoaDon->right;
        } else {
            hoaDon = hoaDon->left;
        }
    }
}


// Tính doanh thu theo ngày, tháng, quý, năm
float tinhDoanhThuTheoNgay(HoaDonNode* root, const char* ngay) {
    if (root == NULL) return 0;
    float doanhThu = 0;
    if (strcmp(root->data.date, ngay) == 0) {
        doanhThu += root->data.totalAmount;
    }
    doanhThu += tinhDoanhThuTheoNgay(root->left, ngay);
    doanhThu += tinhDoanhThuTheoNgay(root->right, ngay);
    return doanhThu;
}

float tinhDoanhThuTheoThang(HoaDonNode* root, const char* thang) {
    if (root == NULL) return 0;
    float doanhThu = 0;
    if (strncmp(root->data.date, thang, 7) == 0) {  // So sánh YYYY-MM
        doanhThu += root->data.totalAmount;
    }
    doanhThu += tinhDoanhThuTheoThang(root->left, thang);
    doanhThu += tinhDoanhThuTheoThang(root->right, thang);
    return doanhThu;
}

float tinhDoanhThuTheoQuy(HoaDonNode* root, int nam, int quy) {
    if (root == NULL) return 0;
    float doanhThu = 0;
    int thangBatDau = (quy - 1) * 3 + 1;
    int thangKetThuc = thangBatDau + 2;
    int namHoaDon, thangHoaDon;
    sscanf(root->data.date, "%d-%d", &namHoaDon, &thangHoaDon);
    if (namHoaDon == nam && thangHoaDon >= thangBatDau && thangHoaDon <= thangKetThuc) {
        doanhThu += root->data.totalAmount;
    }
    doanhThu += tinhDoanhThuTheoQuy(root->left, nam, quy);
    doanhThu += tinhDoanhThuTheoQuy(root->right, nam, quy);
    return doanhThu;
}

float tinhDoanhThuTheoNam(HoaDonNode* root, int nam) {
    if (root == NULL) return 0;
    float doanhThu = 0;
    int namHoaDon;
    sscanf(root->data.date, "%d", &namHoaDon);
    if (namHoaDon == nam) {
        doanhThu += root->data.totalAmount;
    }
    doanhThu += tinhDoanhThuTheoNam(root->left, nam);
    doanhThu += tinhDoanhThuTheoNam(root->right, nam);
    return doanhThu;
}

void phongCoNguoiODongNhat(PhongTroNode *root, PhongTro **phongDongNhat, int *soLuongPhong, int *maxCurrentPeople) {
    if (root != NULL) {
        phongCoNguoiODongNhat(root->left, phongDongNhat, soLuongPhong, maxCurrentPeople);
        if (root->data.currentPeople > *maxCurrentPeople) {
            *maxCurrentPeople = root->data.currentPeople;
            *soLuongPhong = 1;
            *phongDongNhat = (PhongTro*)realloc(*phongDongNhat, (*soLuongPhong) * sizeof(PhongTro));
            (*phongDongNhat)[0] = root->data;
        } else if (root->data.currentPeople == *maxCurrentPeople) {
            (*soLuongPhong)++;
            *phongDongNhat = (PhongTro*)realloc(*phongDongNhat, (*soLuongPhong) * sizeof(PhongTro));
            (*phongDongNhat)[*soLuongPhong - 1] = root->data;
        }
        phongCoNguoiODongNhat(root->right, phongDongNhat, soLuongPhong, maxCurrentPeople);
    }
}

// Hàm hiển thị menu
void showMenu() {
    printf("0.  In thong tin\n");
    printf("1.  Them Nguoi thue\n");
    printf("2.  Them Phong tro\n");
    printf("3.  Them Hoa don\n");
    printf("4.  Them Chi tiet hoa don\n");
    printf("5.  Danh sach hoa don giam dan theo tong tien\n");
    printf("6.  Danh sach hoa don tang dan theo ten nguoi thue\n");
    printf("7.  Thong tin phong co nguoi o dong nhat\n");
    printf("8.  Thong tin hoa don va chi tiet hoa don khi biet ma hoa don\n");
    printf("9.  Liet ke danh sach chi tiet cac Hoa don khi biet Ma khach hang\n");
    printf("10. Thong ke doanh thu cho thue phong theo ngay\n");
    printf("11. Thong ke doanh thu cho thue phong theo thang\n");
    printf("12. Thong ke doanh thu cho thue phong theo quy\n");
    printf("13. Thong ke doanh thu cho thue phong theo ngay\n");
    printf("14. Thoat\n");
}

int main() {
    Node *nguoiThueRoot = NULL;
    PhongTroNode *phongTroRoot = NULL;
    HoaDonNode *hoaDonRoot = NULL;
    ChiTietHoaDonNode *chiTietHoaDonRoot = NULL;
    int m=0;
    int mahoadon;
    int n;
    // Đọc dữ liệu từ các file
    readNguoiThue("nguoi_thue.txt", &nguoiThueRoot);
    readPhongTro("phong_tro.txt", &phongTroRoot);
    readHoaDon("hoa_don.txt", &hoaDonRoot);
    readChiTietHoaDon("ct_hoa_don.txt", &chiTietHoaDonRoot);

    int choice;
    while (1) {
        showMenu();
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        if (choice == 14) break;
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
            case 5: {
            printf("\nDanh sach hoa don giam dan theo tong tien:\n");
            printHoaDonSortedByTotalAmount(hoaDonRoot);
            break;
            }
            case 6: {
            printf("\nDanh sach hoa don tang dan theo ten nguoi thue:\n");
            printHoaDonSortedByRenterName(hoaDonRoot, nguoiThueRoot);
            break;
            }
            case 7:{
            PhongTro *phongDongNhat = NULL;
            int soLuongPhong = 0;
            int maxCurrentPeople = 0;
            phongCoNguoiODongNhat(phongTroRoot, &phongDongNhat, &soLuongPhong, &maxCurrentPeople);

            if (soLuongPhong > 0) {
                printf("\nPhong co nguoi o dong nhat:\n");
                for (int i = 0; i < soLuongPhong; i++) {
                    printf("ID: %d, Ten phong: %s, So nguoi toi da: %d, So nguoi hien tai: %d, Gia thue: %d\n",
                    phongDongNhat[i].id, phongDongNhat[i].name, phongDongNhat[i].maxPeople, phongDongNhat[i].currentPeople, phongDongNhat[i].rentPrice);
        }
    } else {
        printf("Khong co phong nao.\n");
    }

    free(phongDongNhat);
            break;
            }
            case 8:{
            printf("nhap ma hoa don : ");
            scanf("%d",&mahoadon);
            printHoadon(hoaDonRoot,mahoadon);
            printChitietHoadon(chiTietHoaDonRoot,mahoadon);
            break;
            }
            case 9:
                printf("Nhap ID khach hang: ");
                int renterId;
                scanf("%d", &renterId);
                lietKeChiTietHoaDon(nguoiThueRoot, hoaDonRoot, chiTietHoaDonRoot, renterId);
                break;
            case 10:
                printf("Nhap ngay (YYYY-MM-DD): ");
                char ngay[11];
                scanf("%s", ngay);
                printf("Doanh thu ngay %s: %.2f\n", ngay, tinhDoanhThuTheoNgay(hoaDonRoot, ngay));
                break;
            case 11:
                printf("Nhap thang (YYYY-MM): ");
                char thang[8];
                scanf("%s", thang);
                printf("Doanh thu thang %s: %.2f\n", thang, tinhDoanhThuTheoThang(hoaDonRoot, thang));
                break;
            case 12:
                printf("Nhap nam: ");
                int nam, quy;
                scanf("%d", &nam);
                printf("Nhap quy (1-4): ");
                scanf("%d", &quy);
                printf("Doanh thu quy %d nam %d: %.2f\n", quy, nam, tinhDoanhThuTheoQuy(hoaDonRoot, nam, quy));
                break;
            case 13:
                printf("Nhap nam: ");
                scanf("%d", &nam);
                printf("Doanh thu nam %d: %.2f\n", nam, tinhDoanhThuTheoNam(hoaDonRoot, nam));
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }

    return 0;
}
