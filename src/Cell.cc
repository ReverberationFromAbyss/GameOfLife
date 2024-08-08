
export module GameOfLife:Cell;
import std;
import Utils;
import :Defination;
using namespace std;

namespace GameOfLife {

class Cell;

// #include "Cell.inc"
// #include "World.inc"

Cell *Cell::Create(World *parent, Utils::Position pos, bool livingStatus) {
  auto instance = new (std::nothrow) Cell();
  if (!instance->Init(parent, pos, livingStatus)) {
    delete instance;
    instance = nullptr;
  }
  return instance;
}

Cell *Cell::NewInstance(World *parent) { return Create(parent); }

bool Cell::Init(World *parent, Utils::Position pos, bool livingStatus) {

  Utils::log(__FILE__, __LINE__, "Initializing Cell....");

  pair<int, int> neighbors[]{
      {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
  };
  m_parent_ = parent;
  m_currentLivingStatus_ = livingStatus;
  m_pos_ = pos;

  for (int i = 0; i < m_neighbors_.size(); i++) {
    m_neighbors_[i] = Utils::Position(m_pos_.x + neighbors[i].first,
                                      m_pos_.y + neighbors[i].second);
  }

  return true;
}

bool Cell::GetCurrentLivingStatus(void) { return m_currentLivingStatus_; }

void Cell::SetCurrentLivingStatus(bool livingStatus) {
  m_currentLivingStatus_ = livingStatus;
}

void Cell::EvaluateNextStatus(void) {

  int living{0};
  for (auto var : m_neighbors_) {
    auto limit = m_parent_->GetMapScale();
    if (var.x < 0 || var.y < 0 || var.x >= limit.x || var.y >= limit.y) {
      continue;
    }

    if (m_parent_->GetLife(var).m_currentLivingStatus_) {
      living++;
    }
  }
  if (m_currentLivingStatus_) {
    switch (living) {
    case 0:
    case 1:
      m_toBeLive_ = false;
      break;
    case 2:
    case 3:
      m_toBeLive_ = true;
      break;
    case 4:
    default:
      m_toBeLive_ = false;
      break;
    }
  } else {
    if (3 == living) {
      m_toBeLive_ = true;
    }
  }
  return;
}

void Cell::ForwardStatus(void) {

  m_currentLivingStatus_ = m_toBeLive_;
  m_toBeLive_ = false;
  return;
}

} // namespace GameOfLife
