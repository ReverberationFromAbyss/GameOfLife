module;
export module GameOfLife:World;
import std;
import Utils;
import :Defination;

using namespace std;

namespace GameOfLife {

// #include "World.inc"
// #include "Cell.inc"

World *World::s_instance_{nullptr};

World *World::Create(Utils::Position scale) {
  s_instance_ =
      (nullptr == s_instance_) ? new (std::nothrow) World() : s_instance_;
  if (!s_instance_->Init(scale)) {
    delete s_instance_;
    s_instance_ = nullptr;
  }
  return s_instance_;
}

World *World::GetInstance(void) {
  return (nullptr == s_instance_) ? Create() : s_instance_;
}

bool World::Init(Utils::Position scale) {
  m_mapScaleXLimit_ = scale.x;
  m_mapScaleYLimit_ = scale.y;

  Utils::log(__FILE__, __LINE__, "Initializing World...");

  m_map_.resize(m_mapScaleXLimit_);

  for (int i = 0; i < m_mapScaleXLimit_; i++) {
    m_map_[i].reserve(m_mapScaleYLimit_);
    for (int j = 0; j < m_mapScaleYLimit_; j++) {
      m_map_[i][j] = Cell::Create(this, Utils::Position(i, j));
    }
  }

  return true;
}

World::~World() {

  for (int i = 0; i < m_mapScaleXLimit_; i++) {
    for (int j = 0; j < m_mapScaleYLimit_; j++) {
      delete m_map_[i][j];
    }
  }
}

void World::Update(void) {

  for (int i = 0; i < m_mapScaleXLimit_; i++) {
    for (int j = 0; j < m_mapScaleYLimit_; j++) {
      m_map_[i][j]->EvaluateNextStatus();
    }
  }
  for (int i = 0; i < m_mapScaleXLimit_; i++) {
    for (int j = 0; j < m_mapScaleYLimit_; j++) {
      m_map_[i][j]->ForwardStatus();
    }
  }
}
// TODO: Export series
vector<vector<Cell *>> World::ExportMap(void) { return m_map_; }

string World::ExportToString(void) {

  string exp{};

  for (int i = 0; i < m_mapScaleXLimit_; i++) {
    for (int j = 0; j < m_mapScaleYLimit_; j++) {
      exp.push_back(m_map_[i][j]->GetCurrentLivingStatus() ? 'X' : '_');
    }
    exp.append("\n");
  }
  return exp;
}

void World::SetLife(Utils::Position pos, Cell *cell) {
  m_map_[pos.x][pos.y] = (nullptr == cell ? Cell::Create(this, pos) : cell);
}
void World::SetLife(Utils::Position pos, bool livingStatus) {
  m_map_[pos.x][pos.y]->SetCurrentLivingStatus(livingStatus);
}

Cell &World::GetLife(Utils::Position pos) { return *m_map_[pos.x][pos.y]; }

Utils::Position World::GetMapScale(void) {
  return Utils::Position(m_mapScaleXLimit_, m_mapScaleYLimit_);
}

} // namespace GameOfLife
