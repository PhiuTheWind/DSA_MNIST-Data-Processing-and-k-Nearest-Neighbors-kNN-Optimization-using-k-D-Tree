#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

//Constructor function
kDTree::kDTree(int k)
{
    this -> root = nullptr;
    this -> k = k;
    this -> counting = 0;
}

//Destructor function
kDTree::~kDTree()
{
    
}


const kDTree& kDTree::operator=(const kDTree& other) {
   // TODO: insert return statement here
    if (this != &other) { 
        delete this->root;  
        this->k = other.k;
        this->counting = other.counting;
        this->root = this->copyTraversal(other.root);
    }
    return *this;
  
}

kDTree::kDTree(const kDTree &other)
{
    this -> k = other.k;
    copyTraversal(other.root);
    this -> counting = other.counting;
}

void kDTree::re_inorderTraversal(kDTreeNode * node_tree) const
{
    if (node_tree == nullptr) 
    {
        if (root == nullptr)
        {
            return;
        }
        node_tree = root;
    }

    //Gọi đệ quy bên trái 
    if (node_tree -> left != nullptr)
    {
        re_inorderTraversal(node_tree -> left);
    }

    //Sau đó in data của node ra
    if (node_tree -> left != nullptr)
    {
        cout << " (";
    }

    else 
    {   
        cout << "(";
    }

    for (auto i =  node_tree -> data.begin(); true; i++)
    {
        // Bằng `end() - 1` nếu không có nhãn ở phía sau và sẽ trỏ vào phần tử cuối cùng của vector
        // Bằng `end() - 2` nếu có nhãn ở phía sau và sẽ trỏ vào phần tử cuối cùng của vector
        if (i == node_tree->data.end() - (node_tree -> data.size() - k) - 1) 
        {
            cout << *i;
            break;  
        }
    }

    if (node_tree->right != nullptr)
    {
        cout << ") ";
    }   

    else 
    {
        cout << ")";
    }

    //Gọi đệ quy bên phải
    if (node_tree -> right != nullptr)
    {
        re_inorderTraversal(node_tree -> right);
    }
}


void kDTree::inorderTraversal() const
{
    re_inorderTraversal(root);
}

void kDTree::preorderTraversal() const {
    // Gọi hàm đệ quy để thực hiện duyệt cây theo thứ tự Pre-order
  
    this -> re_preorderTraversal(root);
}

void kDTree::re_preorderTraversal(kDTreeNode* node) const {
    
    if (node == nullptr) 
    {
        return;
    }
    // In ra thông tin của node hiện tại tương tự như hàm inorder
    if (node->left != nullptr) {
        cout << "(";
    } else {
        cout << "(";
    }
    for (auto i = node->data.begin(); true; i++) {
        if (i == node->data.end() - (node->data.size() - k) - 1) {
            cout << *i;
            break;
        }
        cout << *i << ", ";
    }
    if (node->right != nullptr) {
        cout << ") ";
    } else {
        cout << ") ";
    }

    // Duyệt sang nút con bên trái
    re_preorderTraversal(node->left);

    // Duyệt sang nút con bên phải
    re_preorderTraversal(node->right);
}

void kDTree::postorderTraversal() const {
    // Gọi hàm đệ quy để thực hiện duyệt cây theo thứ tự Post-order
    this -> re_postorderTraversal(root);
}

void kDTree::re_postorderTraversal(kDTreeNode* node) const {
    if (node == nullptr) {
        return;
    }

    // Duyệt sang nút con bên trái
    re_postorderTraversal(node->left);

    // Duyệt sang nút con bên phải
    re_postorderTraversal(node->right);

    // In ra thông tin của node hiện tại tương tự như hàm inorder
    if (node->left != nullptr) 
    {
        cout << "(";
    } else {
        cout << "(";
    }
    for (auto i = node->data.begin(); true; i++) {
        if (i == node->data.end() - (node->data.size() - k) - 1) {
            cout << *i;
            break;
        }
        cout << *i << ", ";
    }
    if (node->right != nullptr) 
    {
        cout << ") ";
    } 
    else 
    {
        cout << ")";
    }
}

kDTreeNode* kDTree::copyTraversal(const kDTreeNode* temp)
{
    // Base case: Nếu nút nguồn là nullptr, không cần thực hiện gì cả
    if (temp == nullptr) {
        return nullptr;
    }

    // Tạo một nút mới với dữ liệu từ nút nguồn
    kDTreeNode* new_Node = new kDTreeNode(temp->data);

    // Sao chép các nút con của nút nguồn sang nút đích bằng cách gọi đệ quy
    new_Node->left = copyTraversal(temp->left);
    new_Node->right = copyTraversal(temp->right);

    return new_Node;
}


int kDTree::height() const
{
    return this -> re_height(root);
}


int kDTree ::re_height(kDTreeNode *cur_node) const
{
    if (cur_node == nullptr) 
    {
        if (root == nullptr)
        {
            return 0;
        }
        cur_node = root;
    }

    int left_height = 0;
    int right_height = 0;

    //Gọi đệ quy bên trái 
    if (cur_node -> left != nullptr)
    {
        left_height = re_height(cur_node -> left);
    }

    //Gọi đệ quy bên phải
    if (cur_node -> right != nullptr)
    {
        right_height = re_height(cur_node -> right);
    }


    // Chiều cao của cây sẽ là lớn nhất giữa chiều cao của cây con bên trái và cây con bên phải, cộng thêm 1
    return (1 + max(left_height, right_height));
}


int kDTree::nodeCount() const
{
    return this->counting;

}

int kDTree::leafCount() const
{
    return leafCountRec(root);
}

int kDTree::leafCountRec(kDTreeNode *node) const
{
    if(node==nullptr) return 0;
    if(node->left==nullptr && node->right==nullptr) return 1;
    else return leafCountRec(node->left) + leafCountRec(node->right);
}

void kDTree::insert(const vector<int> &point)
{
    this -> root = this -> recInsert(root, point, 0);
    this -> counting++;
}


kDTreeNode* kDTree::recInsert(kDTreeNode* temp, const vector<int> &point, int level) 
{
    // Bước 1: Tìm điều kiện dừng và khởi tạo node mới nếu cần
    if (temp == nullptr) 
    {   
        return new kDTreeNode(point);
    }

    // Bước 2: Tính toán alpha
    int alpha = level % k;

    // Bước 3: So sánh giá trị của hai vector theo chiều alpha
    if (point[alpha] < temp->data[alpha]) 
    {
    // Bước 4: Cập nhật cây con bên trái hoặc bên phải dựa trên so sánh
        temp -> left = recInsert(temp->left, point, level + 1);
    } else 
    {
        temp -> right = recInsert(temp->right, point, level + 1);
    }
    return temp;
}


kDTreeNode *kDTree::findMin(kDTreeNode *node, int d, int level)
{
     if (node == nullptr) {
        return nullptr; // Bước 1: Điều kiện dừng
    }

    int alpha = level % k; // Tính trục hiện tại

    if (alpha == d) {
        // Bước 2: Nếu node đang xét theo chiều alpha
        if (node->left != nullptr) {
            // Tiếp tục tìm kiếm bên trái nếu có
            return findMin(node->left, d, level + 1);
        } else {
            // Con bên trái không có, node hiện tại là nhỏ nhất
            return node;
        }
    } else {
        // Bước 3: Nếu node đang xét khác chiều alpha
        kDTreeNode* leftMin = findMin(node->left, d, level + 1);
        kDTreeNode* rightMin = findMin(node->right, d, level + 1);

        // So sánh để tìm giá trị nhỏ nhất giữa node hiện tại, bên trái và bên phải
        kDTreeNode* minNode = node; // Giả định node hiện tại là nhỏ nhất
        if (leftMin != nullptr && leftMin->data[d] < minNode->data[d]) {
            minNode = leftMin;
        }
        if (rightMin != nullptr && rightMin->data[d] < minNode->data[d]) {
            minNode = rightMin;
        }
        return minNode;
    }
}

kDTreeNode *kDTree::rec_remove(kDTreeNode *node, const vector<int> &point, int level)
{ 
    if (node == nullptr) {
        return nullptr; // Bước 1: Điều kiện dừng, không tìm thấy nút cần xóa
    }

    int cd = level % k; // Chiều hiện tại dựa trên level

    // Kiểm tra nếu node hiện tại chứa điểm cần xóa
    if (node->data == point) {
        // Bước 2: Xóa nếu là node lá
        if (node->left == nullptr && node->right == nullptr) 
        {
            delete node;
            this-> counting--; // Giảm số lượng node trong cây
            return nullptr;
        }

        // Bước 3: Xử lý nếu node không phải là lá
        if (node->right != nullptr) {
            // Ưu tiên tìm node nhỏ nhất theo chiều alpha từ cây con bên phải
            kDTreeNode* minNode = findMin(node->right, cd, level + 1);
            node->data = minNode->data; // Thay thế dữ liệu
            node->right = rec_remove(node->right, minNode->data, level + 1); // Xóa node đã thay thế
        } else {
            // Chuyển nhánh bên trái lên thay thế và xóa nhánh trái
             kDTreeNode* minNode = findMin(node->left, cd, level + 1);
            node->data = minNode->data; // Thay thế dữ liệu node hiện tại bằng node nhỏ nhất bên trái
            node->left = rec_remove(node->left, minNode->data, level + 1); // Xóa node nhỏ nhất bên trái
            node->right = node->left; // Di chuyển cây con bên trái lên thay cho node bên phải
            node->left = nullptr; // Xóa liên kết bên trái cũ
        }
    } else if (point[cd] < node->data[cd]) {
        node->left = rec_remove(node->left, point, level + 1); // Tìm kiếm và xóa trong cây con bên trái
    } else {
        node->right = rec_remove(node->right, point, level + 1); // Tìm kiếm và xóa trong cây con bên phải
    }

    return node;
}


void kDTree::remove(const vector<int> &point)
{
    root = rec_remove(root,point,0);
}

bool kDTree::search(const vector<int> &point)
{
    return rec_seacch(root, point, 0);
}


bool kDTree::rec_seacch(kDTreeNode *temp, const vector<int> &point, int level)
{
    if (temp == nullptr) {
        return false; // Nếu cây con rỗng, điểm không tồn tại trong cây
    }

    // So sánh điểm tại nút hiện tại với điểm cần tìm
    if (temp->data == point) {
        return true; // Nếu điểm được tìm thấy, trả về true
    }

    // Chọn chiều chia
    int alpha = level % k;

    // So sánh giá trị tại chiều alpha của điểm và nút hiện tại
    if (point[alpha] < temp->data[alpha]) {
        return rec_seacch(temp->left, point, level + 1); // Tìm kiếm trong cây con bên trái
    } else {
        return rec_seacch(temp->right, point, level + 1); // Tìm kiếm trong cây con bên phải
    }
}

    int partition(vector<vector<int>> &points, int left, int right, int axis) 
    {
        // Chọn pivot ngẫu nhiên từ mảng
        int pivotIndex = left + rand() % (right - left + 1);
        vector<int> pivot = points[pivotIndex];
        // Di chuyển pivot vào cuối mảng
        swap(points[pivotIndex], points[right]);
        
        int i = left - 1;

        for (int j = left; j <= right - 1; j++) {
            if (points[j][axis] <= pivot[axis]) {
                i++;
                swap(points[i], points[j]);
            }
        }
        swap(points[i + 1], points[right]);
        return i + 1;
    }

    void quickSort(vector<vector<int>> &points, int left, int right, int axis) 
    {
        if (left < right) {
            int pivotIndex = partition(points, left, right, axis);

            quickSort(points, left, pivotIndex - 1, axis);
            quickSort(points, pivotIndex + 1, right, axis);
        }
    }
    void kDTree::buildTree(const vector<vector<int>> &pointList) {
        this->root = this->rec_buildTree(pointList, 0);
    }

    kDTreeNode *kDTree::rec_buildTree(const vector<vector<int>> &pointList, int level) 
    {
        // Bước 0: Kiểm tra điều kiện dừng
    if (pointList.empty()) {
        return nullptr;
    }

    int axis = level % k;
    vector<vector<int>> sortedPoints = pointList;
    quickSort(sortedPoints, 0, sortedPoints.size() - 1, axis);

    size_t midIndex = (sortedPoints.size() - 1) / 2;
    while (midIndex > 0 && sortedPoints[midIndex][axis] == sortedPoints[midIndex - 1][axis]) {
        midIndex--; // Điều chỉnh về bên trái nếu giá trị trùng nhau
    }

    kDTreeNode* node = new kDTreeNode(sortedPoints[midIndex]);
    this->counting++;

    vector<vector<int>> leftPoints(sortedPoints.begin(), sortedPoints.begin() + midIndex);
    vector<vector<int>> rightPoints(sortedPoints.begin() + midIndex + 1, sortedPoints.end());
    node->left = rec_buildTree(leftPoints, level + 1);
    node->right = rec_buildTree(rightPoints, level + 1);

    return node;
}

double kDTree::squaredEuclideanDistance(const vector<int> &a, const vector<int> &b)
{
    double distance = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        distance += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return distance;
}

//nearestNeighbour - start
void kDTree::rec_nearestNeighbour(kDTreeNode *temp, const vector<int> &target, kDTreeNode *&best, int level)
{
    if (temp == nullptr) return;  // Điều kiện dừng khi node duyệt là null

    int alpha = level % this->k;  // Tính giá trị alpha
    double dis = abs(target[alpha] - temp->data[alpha]);  // Khoảng cách hình chiếu của target lên trục alpha

    // Xác định node tiếp theo để duyệt dựa trên giá trị của alpha
    kDTreeNode* next = (target[alpha] < temp->data[alpha]) ? temp->left : temp->right;
    // Duyệt nhánh chính trước
    rec_nearestNeighbour(next, target, best, level + 1);


    // Sau khi đã duyệt một bên, kiểm tra và cập nhật best
    if (best == nullptr || squaredEuclideanDistance(target, temp->data) < squaredEuclideanDistance(target, best->data)) 
    {
        best = temp;  // Cập nhật best nếu temp gần hơn
    }

    // Khoảng cách từ target đến best hiện tại
    double rad = squaredEuclideanDistance(target, best->data);

    // Chỉ kiểm tra nhánh kia nếu d < R và nếu nhánh kia còn có thể cung cấp node gần hơn
    if (dis < rad) {
        kDTreeNode* other = (target[alpha] < temp->data[alpha]) ? temp->right : temp->left;
        rec_nearestNeighbour(other, target, best, level + 1);
    }
}

void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *&best)
{
    best=nullptr;
    rec_nearestNeighbour(root,target,best,0);
}

//nearestNeighbour - end 


//kNearestNeighbour -start
void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
    rec_kNearestNeighbour(root, target, k, bestList, 0);
}

void kDTree::rec_kNearestNeighbour(kDTreeNode *temp, const vector<int> &target, int k, vector<kDTreeNode *> &bestList, int level)
{
    if (temp == nullptr) return;  // Nếu node hiện tại là null, dừng việc duyệt

    int alpha = level % this->k;  // Tính chỉ số chiều hiện tại để so sánh
    double dis = abs(target[alpha] - temp->data[alpha]);  // Khoảng cách từ điểm hiện tại đến mặt phẳng phân chia

    // Chọn nhánh tiếp theo để duyệt dựa trên giá trị tại chiều alpha
    kDTreeNode *nextBranch = (target[alpha] < temp->data[alpha]) ? temp->left : temp->right;
    kDTreeNode *oppositeBranch = (target[alpha] < temp->data[alpha]) ? temp->right : temp->left;

    // Duyệt nhánh ưu tiên trước
    rec_kNearestNeighbour(nextBranch, target, k, bestList, level + 1);

    // Tính khoảng cách Euclidean từ điểm mục tiêu đến node hiện tại
    double radius = squaredEuclideanDistance(target, temp->data);

    if (bestList.size() < k) {
        bestList.push_back(temp);  // Nếu danh sách chưa đầy, thêm node hiện tại vào
        rec_kNearestNeighbour(oppositeBranch, target, k, bestList, level + 1);  // Duyệt nhánh đối diện nếu cần
    } else {
        // Tìm khoảng cách lớn nhất trong danh sách
        double maxDistance = squaredEuclideanDistance(target, bestList[0]->data);
        int maxIndex = 0;
        for (int i = 0; i < k; i++) {
            double currentDistance = squaredEuclideanDistance(target, bestList[i]->data);
            if (currentDistance >= maxDistance) {
                maxDistance = currentDistance;
                maxIndex = i;
            }
        }
        // Nếu node hiện tại gần hơn khoảng cách lớn nhất trong danh sách, thay thế nó
        if (radius < maxDistance) {
            bestList.erase(bestList.begin()+maxIndex);
            bestList.push_back(temp);
               
                // Cập nhật danh sách với node gần hơn
        }

        // Chỉ kiểm tra nhánh đối diện nếu khoảng cách hình chiếu d nhỏ hơn khoảng cách lớn nhất hiện tại trong bestList
        if (!bestList.empty() && dis < maxDistance) {
            rec_kNearestNeighbour(oppositeBranch, target, k, bestList, level + 1);
        }

        for (int i = 0; i < k-1; i++) {
            for (int j = i+1; j < k; j++) {
            if (squaredEuclideanDistance(target, bestList[i]->data) > squaredEuclideanDistance(target, bestList[j]->data)) 
            {
                swap(bestList[i], bestList[j]);
            }
            }
        }
    }
}

void kDTree::buildTreeLable(const vector<vector<int>> &pointList, const vector<int> &label)
{   
    // Đặt số lượng node cho cây
    this->counting = pointList.size();

    // Xây dựng cây từ danh sách các điểm và nhãn tương ứng
    this->root = this->buildTreeLableRec(pointList, label, 0);
}

kDTreeNode* kDTree::buildTreeLableRec(const vector<vector<int>> &pointList, const vector<int> &label, int level)
{
    // Kiểm tra điều kiện dừng: nếu danh sách điểm rỗng, trả về nullptr
    if (pointList.empty()) {
        return nullptr;
    }
    
    // Chọn trục để phân chia các điểm
    int axis = level % k;

    // Tạo một vector chứa cặp điểm và nhãn tương ứng
    vector<pair<vector<int>, int>> pairedPointsLabels;
    for (size_t i = 0; i < pointList.size(); ++i) {
        pairedPointsLabels.push_back({pointList[i], label[i]});
    }

    // Sắp xếp các cặp điểm-nhãn theo giá trị trục
    for (size_t i = 1; i < pairedPointsLabels.size(); ++i) {
        auto key = pairedPointsLabels[i];
        int j = i - 1;
        while (j >= 0 && pairedPointsLabels[j].first[axis] > key.first[axis]) {
            pairedPointsLabels[j + 1] = pairedPointsLabels[j];
            j = j - 1;
        }
        pairedPointsLabels[j + 1] = key;
    }

    // Tìm chỉ số của điểm ở giữa
    size_t midIndex = pairedPointsLabels.size() / 2;
    while (midIndex > 0 && pairedPointsLabels[midIndex].first[axis] == pairedPointsLabels[midIndex - 1].first[axis]) {
        midIndex--; // Điều chỉnh về bên trái nếu các giá trị giống nhau
    }

    // Tạo danh sách các điểm và nhãn bên trái và bên phải của điểm giữa
    vector<vector<int>> leftPoints;
    vector<int> leftLabels;
    vector<vector<int>> rightPoints;
    vector<int> rightLabels;

    for (size_t i = 0; i < midIndex; ++i) {
        leftPoints.push_back(pairedPointsLabels[i].first);
        leftLabels.push_back(pairedPointsLabels[i].second);
    }

    for (size_t i = midIndex + 1; i < pairedPointsLabels.size(); ++i) {
        rightPoints.push_back(pairedPointsLabels[i].first);
        rightLabels.push_back(pairedPointsLabels[i].second);
    }

    // Tạo node mới từ điểm giữa và nhãn tương ứng
    kDTreeNode* node = new kDTreeNode(pairedPointsLabels[midIndex].first, pairedPointsLabels[midIndex].second);
    
    // Xây dựng cây con bên trái và bên phải đệ quy
    node->left = buildTreeLableRec(leftPoints, leftLabels, level + 1);
    node->right = buildTreeLableRec(rightPoints, rightLabels, level + 1);

    return node;
}

void kNN::fit(Dataset &X_train, Dataset &y_train)
{  

    this->X_train = &X_train;
    this->y_train = &y_train;

    if (X_train.data.size()) 
    {
        int dimension = X_train.data.front().size();
        training.k = dimension;
        vector<vector<int>> pointList ;
        pointList.reserve(X_train.data.size());
        for (const auto& sublist : X_train.data) 
        {
            vector<int> subVec(sublist.begin(), sublist.end());  // Chuyển đổi list<int> thành vector<int>
            pointList.push_back(subVec);  // Thêm subVec vào vec chính
        }
        vector<int> label;
        for (auto it = y_train.data.begin(); it != y_train.data.end(); ++it) {
            if (!it->empty()) {  // Kiểm tra xem vector không rỗng
                label.push_back(it->front());  // Giả định rằng mỗi vector chỉ chứa một nhãn
            }
        }
        training.buildTreeLable(pointList, label);
    }
}
   
int findMostFrequentLabel(const std::vector<kDTreeNode*>& nodeList) {
    // Khởi tạo một vector để đếm số lần xuất hiện của mỗi nhãn, giả sử có tối đa 10 nhãn
    std::vector<int> labelOccurrences(10, 0);  // Thay đổi giá trị 10 nếu nhãn của bạn có giới hạn khác
    
    // Duyệt qua danh sách các node và đếm số lần xuất hiện của mỗi nhãn
    for (const auto& node : nodeList) {
        if (node != nullptr) {
            labelOccurrences[node->label]++;  // Tăng số lần xuất hiện của nhãn tương ứng
        }
    }

    // Khởi tạo biến lưu trữ nhãn xuất hiện nhiều nhất và số lần xuất hiện tối đa
    int mostFrequentLabel = 0;
    int maxOccurrences = 0;

    // Duyệt qua vector đếm số lần xuất hiện của mỗi nhãn
    for (int i = 0; i < labelOccurrences.size(); ++i) {
        // Nếu số lần xuất hiện của nhãn hiện tại lớn hơn số lần xuất hiện tối đa hiện tại
        if (labelOccurrences[i] > maxOccurrences) {
            // Cập nhật nhãn xuất hiện nhiều nhất và số lần xuất hiện tối đa
            maxOccurrences = labelOccurrences[i];
            mostFrequentLabel = i;
        }
    }

    // Trả về nhãn xuất hiện nhiều nhất
    return mostFrequentLabel;
}


// Chuyển đổi một vector<vector<int>> thành một list<list<int>>
list<list<int>> convertVectorToList(const vector<vector<int>> &source)
{
    list<list<int>> result;

    // Duyệt qua mỗi vector<int> trong vector<vector<int>>
    for (const auto& innerVector : source) {
        // Chuyển đổi vector<int> thành list<int> và thêm vào list chính
        list<int> sublist(innerVector.begin(), innerVector.end());
        result.push_back(sublist);
    }

    // Trả về list đã chuyển đổi
    return result;
}

// Chuyển đổi một list<list<int>> thành một vector<vector<int>>
vector<vector<int>> convertListToVector(const list<list<int>> &source)
{
    vector<vector<int>> result;
    result.reserve(source.size()); // Tối ưu hóa bằng cách đặt trước kích thước của vector

    // Duyệt qua mỗi list<int> trong list<list<int>>
    for (const auto& innerList : source) {
        // Chuyển đổi list<int> thành vector<int> và thêm vào vector chính
        vector<int> subVec(innerList.begin(), innerList.end());
        result.push_back(subVec);
    }

    // Trả về vector đã chuyển đổi
    return result;
}

Dataset kNN::predict(Dataset &X_test) 
{
    // Tạo một Dataset mới để lưu kết quả dự đoán
    Dataset result;
    // Thêm tên cột cho nhãn vào dataset kết quả
    result.columnName.push_back("label");

    // Chuyển đổi danh sách dữ liệu kiểm tra từ list sang vector
    vector<vector<int>> testData = convertListToVector(X_test.data);
    
    // Vector để lưu dự đoán
    vector<int> predictions;
    // Duyệt qua từng mẫu trong dữ liệu kiểm tra
    for(const auto& target : testData) {
        // Tìm các láng giềng gần nhất của mẫu hiện tại
        vector<kDTreeNode*> nearestNeighbors;
        training.kNearestNeighbour(target, this->k, nearestNeighbors);
        
        // Dự đoán nhãn dựa trên láng giềng gần nhất và thêm vào vector dự đoán
        int predictedLabel = findMostFrequentLabel(nearestNeighbors);
        predictions.push_back(predictedLabel);
    }
    
    // Tạo dữ liệu dự đoán từ các nhãn đã dự đoán
    for(const auto& label : predictions) {
        std::list<int> row; // Tạo một list mới cho mỗi nhãn
        row.push_back(label);
        result.data.push_back(row);  // Thêm vào data của result
    }   
    return result;
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    // Kiểm tra nếu một trong hai dataset rỗng
    if (y_test.data.empty() || y_pred.data.empty()) {
        return 0.0; // Trả về 0 nếu một trong các dataset rỗng
    }

    // Khởi tạo iterator cho dataset thực tế và dataset dự đoán
    auto it_test = y_test.data.begin();
    auto it_pred = y_pred.data.begin();
    int correctCount = 0; // Số lượng dự đoán chính xác
    int total = 0; // Tổng số mẫu

    // Duyệt qua cả hai dataset
    while (it_test != y_test.data.end() && it_pred != y_pred.data.end()) {
        // Giả định rằng mỗi danh sách chỉ chứa một nhãn
        if (!it_test->empty() && !it_pred->empty() && it_test->front() == it_pred->front()) {
            correctCount++; // Tăng số lượng dự đoán chính xác nếu nhãn thực tế và nhãn dự đoán giống nhau
        }
        ++it_test;
        ++it_pred;
        ++total; // Tăng tổng số mẫu
    }

    // Kiểm tra tránh chia cho 0
    if (total == 0) return 0.0;

    // Tính tỉ lệ dự đoán chính xác và trả về
    return static_cast<double>(correctCount) / total;
}
