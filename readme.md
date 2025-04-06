# Dice Puzzle

A first-person puzzle game mechanic implemented in Unreal Engine 5, featuring a unique crescent-shaped dice movement system on a diagonal grid.

## Project Links
* **Video Demo**: [Watch on Google Drive](https://drive.google.com/file/d/1XMa1J4lRCqCPgQKKU0o3r0ZvLztleqpf/view?usp=sharing)

## Technical Requirements
* **Engine**: Unreal Engine 5.3.2
* **IDE**: Rider
* **Development Platform**: Windows

## Controls
* **Movement**: W, A, S, D keys
* **Change Crescent Piece**: C key

## Overview

Dice Puzzle is an interactive puzzle mechanic where players navigate crescent-shaped dice through a grid-based track system. The goal is to guide all dice to a central position using only diagonal paths, creating an engaging and challenging puzzle experience.

## Features

### Core Mechanics
- First-person to puzzle-view camera transitions
- Interactive crescent-shaped dice with precise movement controls
- Central goal position with completion validation
- Subtle visual feedback system

### Player Interaction
1. **Discovery Phase**
   - First-person exploration
   - Interactive plaque for puzzle activation
   - Smooth camera transition to puzzle view

2. **Puzzle Mechanics**
   - Individual dice selection with highlight feedback
   - Diagonal movement along predefined tracks
   - Rule-based movement constraints
   - Multi-dice positioning challenge

### Technical Implementation

#### Movement Rules
- Dice movement restricted to diagonal tracks
- No jumping over other dice allowed
- Single occupancy per grid space
- Forward progression toward center required
- No backtracking permitted

#### UI/UX Features
- Minimalist design with no explicit HUD
- Subtle highlighting for selected dice
- Smooth camera transitions
- Clear visual feedback for valid moves

## Technical Details

### Camera System
- Interpolated camera transitions
- Fixed puzzle view angles
- Collision prevention system
- Automatic return transition on completion

### Core Systems
- State management for puzzle progression
- Collision detection and prevention
- Movement validation system
- Completion state verification

## Testing Features

### Verification Points
- Movement accuracy and constraints
- Collision detection reliability
- Camera transition smoothness
- State consistency management
- Completion condition validation

### Edge Cases Handled
- Rapid input processing
- Multiple dice selection scenarios
- Interrupt handling mechanisms
- State recovery systems

## Installation

1. Clone the repository:
```bash
git clone https://github.com/vaiv26/FirstPerson3DPuzzleMockup.git
```
2. Open the project in Unreal Engine 5.3.2
3. Build and run the project using Rider or your preferred IDE

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

