#pragma once
#include <string>

const std::string INDEX_HTML = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Brain Tester — Master DSA Through Play</title>
  <meta name="description" content="Challenge your mind with 6 algorithm-based puzzles: BFS, Dynamic Programming, Greedy, Backtracking and more.">
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700;800&family=Outfit:wght@600;700;800&display=swap" rel="stylesheet">
  <style>
    /* ======================================================================
       DESIGN SYSTEM
       ====================================================================== */
    :root {
      --bg-deep:    #06080f;
      --bg-base:    #0b1022;
      --bg-surface: rgba(15, 23, 48, 0.65);
      --bg-card:    rgba(20, 30, 60, 0.55);
      --bg-elevated:rgba(25, 38, 75, 0.5);
      --border:     rgba(100, 120, 180, 0.15);
      --border-glow:rgba(139, 92, 246, 0.4);
      --glass-blur: 18px;

      --accent-1:   #7c3aed;
      --accent-2:   #a855f7;
      --accent-3:   #c084fc;
      --cyan:       #06b6d4;
      --emerald:    #10b981;
      --amber:      #f59e0b;
      --rose:       #f43f5e;

      --text:       #f1f5f9;
      --text-muted: #94a3b8;
      --text-dim:   #64748b;

      --font-body:  'Inter', system-ui, -apple-system, sans-serif;
      --font-display:'Outfit', 'Inter', sans-serif;

      --radius-sm:  8px;
      --radius-md:  14px;
      --radius-lg:  20px;
      --radius-xl:  28px;

      --shadow-glow: 0 0 40px rgba(124, 58, 237, 0.15), 0 0 80px rgba(124, 58, 237, 0.05);
      --shadow-card: 0 8px 32px rgba(0, 0, 0, 0.4);
      --shadow-modal:0 24px 80px rgba(0, 0, 0, 0.65);

      --transition-fast: 0.15s cubic-bezier(0.4, 0, 0.2, 1);
      --transition-med:  0.3s cubic-bezier(0.4, 0, 0.2, 1);
      --transition-slow: 0.5s cubic-bezier(0.4, 0, 0.2, 1);
    }

    [data-theme="light"] {
      --bg-deep:    #f1f5f9;
      --bg-base:    #ffffff;
      --bg-surface: rgba(255, 255, 255, 0.85);
      --bg-card:    rgba(255, 255, 255, 0.82);
      --bg-elevated:rgba(241, 245, 249, 0.9);
      --border:     rgba(100, 116, 139, 0.22);
      --border-glow:rgba(124, 58, 237, 0.45);

      --accent-1:   #6d28d9;
      --accent-2:   #7c3aed;
      --accent-3:   #6d28d9;
      --cyan:       #0891b2;
      --emerald:    #059669;
      --amber:      #d97706;
      --rose:       #e11d48;

      --text:       #0f172a;
      --text-muted: #475569;
      --text-dim:   #64748b;

      --shadow-glow: 0 10px 35px rgba(109, 40, 217, 0.14), 0 4px 14px rgba(15, 23, 42, 0.06);
      --shadow-card: 0 8px 24px rgba(15, 23, 42, 0.07);
      --shadow-modal:0 24px 64px rgba(15, 23, 42, 0.18);
    }

    /* ======================================================================
       RESET & BASE
       ====================================================================== */
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    body {
      font-family: var(--font-body);
      background: var(--bg-deep);
      color: var(--text);
      min-height: 100vh;
      overflow-x: hidden;
      -webkit-font-smoothing: antialiased;
    }

    /* ======================================================================
       ANIMATED BACKGROUND
       ====================================================================== */
    .bg-canvas {
      position: fixed; inset: 0; z-index: 0; pointer-events: none; overflow: hidden;
    }
    .bg-orb {
      position: absolute; border-radius: 50%; filter: blur(100px); opacity: 0.35;
      animation: orbFloat 20s ease-in-out infinite alternate;
    }
    .bg-orb:nth-child(1) {
      width: 600px; height: 600px; top: -10%; left: -5%;
      background: radial-gradient(circle, #7c3aed 0%, transparent 70%);
      animation-duration: 22s;
    }
    .bg-orb:nth-child(2) {
      width: 500px; height: 500px; top: 50%; right: -10%;
      background: radial-gradient(circle, #06b6d4 0%, transparent 70%);
      animation-duration: 18s; animation-delay: -5s;
    }
    .bg-orb:nth-child(3) {
      width: 400px; height: 400px; bottom: -5%; left: 30%;
      background: radial-gradient(circle, #a855f7 0%, transparent 70%);
      animation-duration: 25s; animation-delay: -10s;
    }
    @keyframes orbFloat {
      0%   { transform: translate(0, 0) scale(1); }
      33%  { transform: translate(40px, -30px) scale(1.05); }
      66%  { transform: translate(-20px, 20px) scale(0.95); }
      100% { transform: translate(30px, -10px) scale(1.02); }
    }

    /* Stars */
    .bg-stars {
      position: absolute; inset: 0;
      background-image:
        radial-gradient(1px 1px at 10% 20%, rgba(255,255,255,0.4) 50%, transparent 100%),
        radial-gradient(1px 1px at 30% 60%, rgba(255,255,255,0.3) 50%, transparent 100%),
        radial-gradient(1px 1px at 50% 10%, rgba(255,255,255,0.5) 50%, transparent 100%),
        radial-gradient(1px 1px at 70% 80%, rgba(255,255,255,0.3) 50%, transparent 100%),
        radial-gradient(1px 1px at 90% 40%, rgba(255,255,255,0.4) 50%, transparent 100%),
        radial-gradient(1.5px 1.5px at 15% 85%, rgba(255,255,255,0.25) 50%, transparent 100%),
        radial-gradient(1.5px 1.5px at 85% 15%, rgba(255,255,255,0.25) 50%, transparent 100%);
      animation: twinkle 4s ease-in-out infinite alternate;
    }
    @keyframes twinkle { 0% { opacity: 0.6; } 100% { opacity: 1; } }

    /* ======================================================================
       LAYOUT WRAPPER
       ====================================================================== */
    .app {
      position: relative; z-index: 1;
      display: flex; flex-direction: column; align-items: center;
      min-height: 100vh; padding: 0 24px 60px;
    }

    /* ======================================================================
       TOP STATS BAR
       ====================================================================== */
    .top-bar {
      width: 100%; max-width: 1020px;
      display: flex; align-items: center; justify-content: space-between;
      padding: 16px 0; margin-bottom: 8px;
    }
    .top-bar-stats {
      display: flex; gap: 20px; align-items: center;
    }
    .stat-chip {
      display: flex; align-items: center; gap: 6px;
      background: var(--bg-card);
      backdrop-filter: blur(var(--glass-blur));
      border: 1px solid var(--border);
      border-radius: 100px; padding: 6px 16px;
      font-size: 0.82rem; font-weight: 600; color: var(--text-muted);
      transition: border-color var(--transition-fast);
    }
    .stat-chip:hover { border-color: var(--border-glow); }
    .stat-chip .val { color: var(--text); }
    .stat-chip .icon { font-size: 1rem; }
    .btn-leaderboard {
      background: var(--bg-card);
      backdrop-filter: blur(var(--glass-blur));
      border: 1px solid var(--border);
      border-radius: 100px; padding: 8px 20px;
      color: var(--accent-3); font-weight: 600; font-size: 0.82rem;
      cursor: pointer; transition: all var(--transition-fast);
      font-family: var(--font-body);
    }
    .btn-leaderboard:hover {
      border-color: var(--accent-2); background: rgba(124, 58, 237, 0.12);
      transform: translateY(-1px);
    }
    .btn-sound {
      background: var(--bg-card);
      backdrop-filter: blur(var(--glass-blur));
      border: 1px solid var(--border);
      border-radius: 50%; width: 36px; height: 36px;
      display: flex; align-items: center; justify-content: center;
      cursor: pointer; font-size: 1rem; transition: all var(--transition-fast);
    }
    .btn-sound:hover { border-color: var(--accent-2); }

    /* Theme Toggle Sliding Button */
    .theme-switch {
      position: relative;
      width: 64px; height: 36px;
      background: var(--bg-card);
      backdrop-filter: blur(var(--glass-blur));
      border: 1px solid var(--border);
      border-radius: 100px;
      cursor: pointer;
      display: inline-flex; align-items: center; justify-content: space-between;
      padding: 0 7px;
      transition: all var(--transition-med);
      user-select: none;
    }
    .theme-switch:hover { border-color: var(--accent-2); }
    .theme-switch .ts-icon {
      font-size: 0.82rem; line-height: 1; z-index: 1;
      opacity: 0.65;
    }
    .theme-switch .ts-thumb {
      position: absolute;
      top: 3px; left: 3px;
      width: 28px; height: 28px;
      border-radius: 50%;
      background: linear-gradient(135deg, var(--accent-1), var(--accent-2));
      box-shadow: 0 2px 8px rgba(124, 58, 237, 0.4);
      display: flex; align-items: center; justify-content: center;
      font-size: 0.85rem; line-height: 1;
      transition: transform 0.3s cubic-bezier(0.4, 0, 0.2, 1);
      z-index: 2;
    }
    [data-theme="light"] .theme-switch .ts-thumb {
      transform: translateX(28px);
    }

    /* ======================================================================
       HEADER
       ====================================================================== */
    header {
      text-align: center; margin: 32px 0 36px;
    }
    header h1 {
      font-family: var(--font-display);
      font-size: 3.2rem; font-weight: 800; letter-spacing: -0.02em;
      background: linear-gradient(135deg, #818cf8 0%, #c084fc 40%, #f0abfc 70%, #818cf8 100%);
      background-size: 200% 200%;
      -webkit-background-clip: text; background-clip: text;
      -webkit-text-fill-color: transparent;
      animation: gradientShift 6s ease-in-out infinite;
    }
    @keyframes gradientShift {
      0%, 100% { background-position: 0% 50%; }
      50% { background-position: 100% 50%; }
    }
    header .tagline {
      color: var(--text-muted); margin-top: 8px; font-size: 1rem;
      font-weight: 500; letter-spacing: 0.01em;
    }
    header .tagline span {
      color: var(--accent-3); font-weight: 600;
    }

    /* ======================================================================
       GAME CARDS GRID
       ====================================================================== */
    .grid-cards {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 20px;
      max-width: 1020px; width: 100%;
    }
    @media (max-width: 900px) { .grid-cards { grid-template-columns: repeat(2, 1fr); } }
    @media (max-width: 580px) { .grid-cards { grid-template-columns: 1fr; } }

    .card {
      position: relative;
      background: var(--bg-card);
      backdrop-filter: blur(var(--glass-blur));
      border: 1px solid var(--border);
      border-radius: var(--radius-lg);
      padding: 28px 24px 24px;
      display: flex; flex-direction: column; justify-content: space-between;
      transition: all var(--transition-med);
      overflow: hidden;
      cursor: default;
    }
    .card::before {
      content: '';
      position: absolute; top: 0; left: 0; right: 0; height: 3px;
      background: linear-gradient(90deg, var(--accent-1), var(--accent-2), var(--cyan));
      opacity: 0; transition: opacity var(--transition-med);
    }
    .card:hover {
      transform: translateY(-6px);
      border-color: var(--border-glow);
      box-shadow: var(--shadow-glow);
    }
    .card:hover::before { opacity: 1; }

    .card-icon {
      width: 52px; height: 52px; border-radius: var(--radius-md);
      background: rgba(124, 58, 237, 0.12);
      display: flex; align-items: center; justify-content: center;
      font-size: 1.6rem; margin-bottom: 16px;
      border: 1px solid rgba(124, 58, 237, 0.15);
      transition: transform var(--transition-med);
    }
    .card:hover .card-icon { transform: scale(1.1) rotate(-4deg); }

    .card h3 {
      font-family: var(--font-display);
      font-size: 1.2rem; font-weight: 700; margin-bottom: 4px;
    }
    .algo-tag {
      display: inline-block;
      font-size: 0.7rem; font-weight: 700; letter-spacing: 0.04em;
      text-transform: uppercase;
      color: var(--accent-3);
      margin-bottom: 10px;
    }
    .card-desc {
      color: var(--text-muted); font-size: 0.85rem; line-height: 1.55;
      margin-bottom: 20px; flex: 1;
    }
    .card-footer {
      display: flex; align-items: center; justify-content: space-between;
    }
    .card-best {
      font-size: 0.75rem; color: var(--text-dim); font-weight: 500;
    }
    .card-best b { color: var(--amber); }

    .btn-play {
      position: relative; overflow: hidden;
      background: linear-gradient(135deg, var(--accent-1), var(--accent-2));
      color: white; border: none; border-radius: var(--radius-sm);
      padding: 10px 22px; font-weight: 700; font-size: 0.85rem;
      cursor: pointer; font-family: var(--font-body);
      transition: all var(--transition-fast);
      letter-spacing: 0.02em;
    }
    .btn-play:hover {
      transform: translateY(-1px);
      box-shadow: 0 4px 20px rgba(124, 58, 237, 0.4);
    }
    .btn-play:active { transform: scale(0.97); }
    .btn-play .ripple {
      position: absolute; border-radius: 50%; background: rgba(255,255,255,0.3);
      transform: scale(0); animation: rippleAnim 0.5s ease-out;
    }
    @keyframes rippleAnim { to { transform: scale(4); opacity: 0; } }

    /* ======================================================================
       LEADERBOARD PANEL
       ====================================================================== */
    .lb-overlay {
      position: fixed; inset: 0; background: rgba(6, 8, 15, 0.6);
      backdrop-filter: blur(4px);
      z-index: 200; display: none; align-items: stretch; justify-content: flex-end;
    }
    .lb-overlay.open { display: flex; }
    .lb-panel {
      width: 400px; max-width: 90vw;
      background: var(--bg-base);
      border-left: 1px solid var(--border);
      padding: 32px 24px;
      overflow-y: auto;
      animation: slideIn 0.35s var(--transition-med);
    }
    @keyframes slideIn { from { transform: translateX(100%); } to { transform: translateX(0); } }
    .lb-panel h2 {
      font-family: var(--font-display); font-size: 1.5rem; margin-bottom: 8px;
    }
    .lb-panel .lb-subtitle { color: var(--text-muted); font-size: 0.85rem; margin-bottom: 20px; }
    .lb-tabs {
      display: flex; gap: 4px; margin-bottom: 16px;
      background: rgba(15, 23, 48, 0.8); border-radius: var(--radius-sm); padding: 3px;
    }
    .lb-tab {
      flex: 1; text-align: center; padding: 7px 0; border-radius: 6px;
      font-size: 0.78rem; font-weight: 600; color: var(--text-muted);
      cursor: pointer; border: none; background: transparent;
      transition: all var(--transition-fast); font-family: var(--font-body);
    }
    .lb-tab.active { background: var(--accent-1); color: white; }
    .lb-entry {
      display: flex; align-items: center; gap: 12px;
      padding: 12px 14px; border-radius: var(--radius-sm);
      background: var(--bg-card); border: 1px solid var(--border);
      margin-bottom: 8px; transition: border-color var(--transition-fast);
    }
    .lb-entry:hover { border-color: var(--border-glow); }
    .lb-rank {
      width: 28px; height: 28px; border-radius: 50%;
      display: flex; align-items: center; justify-content: center;
      font-size: 0.78rem; font-weight: 800; flex-shrink: 0;
      background: rgba(100, 116, 139, 0.2); color: var(--text-muted);
    }
    .lb-rank.gold   { background: rgba(245, 158, 11, 0.2); color: #fbbf24; }
    .lb-rank.silver { background: rgba(148, 163, 184, 0.2); color: #cbd5e1; }
    .lb-rank.bronze { background: rgba(180, 120, 60, 0.2); color: #d4a574; }
    .lb-info { flex: 1; }
    .lb-game { font-size: 0.85rem; font-weight: 600; }
    .lb-meta { font-size: 0.72rem; color: var(--text-dim); margin-top: 2px; }
    .lb-score { font-weight: 800; color: var(--amber); font-size: 0.95rem; }
    .lb-empty { text-align: center; padding: 40px 0; color: var(--text-dim); font-size: 0.9rem; }
    .lb-close {
      position: absolute; top: 20px; right: 20px;
      width: 32px; height: 32px; border-radius: 50%;
      background: rgba(30, 41, 59, 0.8); border: 1px solid var(--border);
      color: var(--text-muted); font-size: 1rem;
      cursor: pointer; display: flex; align-items: center; justify-content: center;
      transition: all var(--transition-fast);
    }
    .lb-close:hover { background: var(--rose); color: white; border-color: var(--rose); }
    .btn-clear-lb {
      width: 100%; margin-top: 12px; padding: 10px;
      background: rgba(244, 63, 94, 0.1); border: 1px solid rgba(244, 63, 94, 0.3);
      border-radius: var(--radius-sm); color: var(--rose);
      font-size: 0.8rem; font-weight: 600; cursor: pointer;
      transition: all var(--transition-fast); font-family: var(--font-body);
    }
    .btn-clear-lb:hover { background: rgba(244, 63, 94, 0.2); }

    /* ======================================================================
       GAME MODAL
       ====================================================================== */
    .modal-backdrop {
      position: fixed; inset: 0;
      background: rgba(6, 8, 15, 0.78);
      backdrop-filter: blur(6px);
      display: none; align-items: center; justify-content: center;
      z-index: 100;
    }
    .modal-backdrop.open { display: flex; }

    .modal {
      background: var(--bg-base);
      border: 1px solid var(--border);
      border-radius: var(--radius-xl);
      width: 620px; max-width: 95vw;
      padding: 30px 28px 28px;
      position: relative;
      box-shadow: var(--shadow-modal);
      text-align: center;
      max-height: 92vh; overflow-y: auto;
      animation: modalIn 0.35s cubic-bezier(0.16, 1, 0.3, 1);
    }
    @keyframes modalIn {
      from { opacity: 0; transform: scale(0.92) translateY(20px); }
      to   { opacity: 1; transform: scale(1) translateY(0); }
    }
    .modal::-webkit-scrollbar { width: 6px; }
    .modal::-webkit-scrollbar-track { background: transparent; }
    .modal::-webkit-scrollbar-thumb { background: var(--border); border-radius: 3px; }

    .close-btn {
      position: absolute; top: 16px; right: 18px;
      width: 34px; height: 34px; border-radius: 50%;
      background: rgba(30, 41, 59, 0.7); border: 1px solid var(--border);
      color: var(--text-muted); font-size: 1rem;
      cursor: pointer; display: flex; align-items: center; justify-content: center;
      transition: all var(--transition-fast); z-index: 2;
    }
    .close-btn:hover { background: var(--rose); color: white; border-color: var(--rose); }

    .modal-header {
      margin-bottom: 6px;
    }
    #modal-title {
      font-family: var(--font-display);
      font-size: 1.5rem; font-weight: 700; margin: 0;
    }
    #modal-desc {
      color: var(--text-muted); font-size: 0.82rem; margin: 6px 0 4px;
      line-height: 1.5;
    }

    /* Difficulty selector */
    .diff-selector {
      display: flex; gap: 4px; justify-content: center; margin: 12px 0 16px;
      background: rgba(15, 23, 48, 0.8); border-radius: var(--radius-sm);
      padding: 3px; display: inline-flex;
    }
    .diff-btn {
      padding: 7px 20px; border-radius: 6px;
      border: none; background: transparent;
      color: var(--text-muted); font-size: 0.8rem; font-weight: 600;
      cursor: pointer; transition: all var(--transition-fast);
      font-family: var(--font-body);
    }
    .diff-btn.active {
      background: var(--accent-1); color: white;
      box-shadow: 0 2px 10px rgba(124, 58, 237, 0.3);
    }
    .diff-btn:hover:not(.active) { color: var(--text); }

    /* Status bar */
    .status-bar {
      background: rgba(10, 16, 34, 0.7);
      border: 1px solid var(--border); border-radius: var(--radius-md);
      padding: 10px 18px; margin: 0 0 18px;
      display: flex; justify-content: space-around; flex-wrap: wrap; gap: 8px;
      font-size: 0.82rem; font-weight: 600;
    }
    .status-bar span { display: flex; align-items: center; gap: 4px; }
    .status-bar b { color: var(--accent-3); }

    /* Timer */
    .timer-display {
      display: flex; align-items: center; gap: 4px;
      font-variant-numeric: tabular-nums;
    }
    .timer-display b { color: var(--cyan) !important; }

    /* Board */
    .board {
      display: inline-grid; gap: 3px;
      background: rgba(10, 16, 34, 0.6);
      padding: 14px; border-radius: var(--radius-md);
      border: 1px solid var(--border);
      margin-bottom: 14px;
    }

    .cell {
      width: 52px; height: 52px; border-radius: var(--radius-sm);
      background: rgba(30, 41, 59, 0.7);
      display: flex; align-items: center; justify-content: center;
      font-size: 1.05rem; cursor: pointer; user-select: none;
      border: 2px solid transparent;
      transition: all var(--transition-fast);
      position: relative;
    }
    .cell:hover { background: rgba(40, 53, 72, 0.8); }
    .cell.valid {
      border-color: var(--emerald);
      background: rgba(16, 185, 129, 0.12);
      animation: cellPulse 1.5s ease-in-out infinite;
    }
    @keyframes cellPulse {
      0%, 100% { box-shadow: 0 0 0 0 rgba(16, 185, 129, 0.2); }
      50% { box-shadow: 0 0 0 4px rgba(16, 185, 129, 0.1); }
    }
    .cell.player { background: rgba(124, 58, 237, 0.25); border-color: var(--accent-2); }
    .cell.wall   { background: rgba(10, 14, 26, 0.9); }
    .cell.key    { background: rgba(245, 158, 11, 0.12); border-color: rgba(245, 158, 11, 0.5); }
    .cell.lock   { background: rgba(244, 63, 94, 0.1); border-color: rgba(244, 63, 94, 0.4); }
    .cell.cherry { background: rgba(244, 63, 94, 0.08); }
    .cell.thorn  { background: rgba(10, 14, 26, 0.9); }
    .cell.white-sq { background: #e2e8f0; color: #0f172a; font-weight: 700; }
    .cell.black-sq { background: #334155; color: var(--text); font-weight: 700; }
    .cell.sudoku-given  { background: rgba(30, 41, 59, 0.8); color: var(--accent-3); font-weight: 700; }
    .cell.sudoku-empty  { background: rgba(10, 14, 26, 0.7); color: var(--emerald); cursor: text; }
    .cell.sudoku-wrong  { border-color: var(--rose); animation: shake 0.3s ease-in-out; }
    .cell.sudoku-correct{ border-color: var(--emerald); }
    .cell.selected-cell { border-color: var(--amber) !important; box-shadow: 0 0 12px rgba(245, 158, 11, 0.3); }

    /* Sudoku 3x3 box borders — high contrast */
    .sudoku-border-right { border-right: 3px solid #a78bfa !important; }
    .sudoku-border-bottom { border-bottom: 3px solid #a78bfa !important; }
    [data-theme="light"] .sudoku-border-right { border-right: 3px solid #4f46e5 !important; }
    [data-theme="light"] .sudoku-border-bottom { border-bottom: 3px solid #4f46e5 !important; }

    /* Sudoku board wrapper polish */
    .board.sudoku-board {
      background: rgba(8, 12, 28, 0.85);
      border: 3px solid #a78bfa;
      border-radius: var(--radius-md);
      padding: 10px;
      gap: 2px;
      box-shadow: 0 0 24px rgba(167, 139, 250, 0.15), inset 0 0 30px rgba(0,0,0,0.2);
    }
    [data-theme="light"] .board.sudoku-board {
      background: rgba(226, 232, 240, 0.9);
      border-color: #4f46e5;
      box-shadow: 0 0 24px rgba(79, 70, 229, 0.12), inset 0 0 20px rgba(255,255,255,0.3);
    }

    /* Sudoku cell refinements */
    .sudoku-board .cell {
      border-radius: 4px;
      font-weight: 600;
      transition: all 0.12s ease;
    }
    .sudoku-board .cell.sudoku-given {
      background: rgba(30, 41, 59, 0.9);
      color: #c4b5fd;
      font-weight: 800;
      font-size: 1.15rem;
    }
    .sudoku-board .cell.sudoku-empty {
      background: rgba(15, 20, 40, 0.6);
    }
    .sudoku-board .cell.sudoku-empty:hover {
      background: rgba(124, 58, 237, 0.15);
      box-shadow: 0 0 8px rgba(124, 58, 237, 0.2);
    }
    [data-theme="light"] .sudoku-board .cell.sudoku-given {
      background: rgba(238, 242, 255, 0.95);
      color: #4338ca;
    }
    [data-theme="light"] .sudoku-board .cell.sudoku-empty {
      background: #ffffff;
    }
    [data-theme="light"] .sudoku-board .cell.sudoku-empty:hover {
      background: rgba(99, 102, 241, 0.08);
    }

    /* Sudoku numpad polish */
    .sudoku-numpad-enhanced {
      display: flex; gap: 8px; justify-content: center; flex-wrap: wrap;
      margin-top: 14px;
    }
    .sudoku-numpad-enhanced button {
      width: 44px; height: 44px; border-radius: 10px;
      border: 1px solid rgba(167, 139, 250, 0.3);
      background: rgba(30, 41, 59, 0.7);
      color: var(--text); font-size: 1.1rem; font-weight: 700;
      cursor: pointer; transition: all 0.15s ease;
      font-family: var(--font-body);
    }
    .sudoku-numpad-enhanced button:hover {
      background: linear-gradient(135deg, var(--accent-1), var(--accent-2));
      border-color: var(--accent-2);
      transform: translateY(-2px);
      box-shadow: 0 4px 14px rgba(124, 58, 237, 0.35);
      color: white;
    }
    .sudoku-numpad-enhanced button:active {
      transform: scale(0.95);
    }
    [data-theme="light"] .sudoku-numpad-enhanced button {
      background: rgba(238, 242, 255, 0.9);
      border-color: rgba(99, 102, 241, 0.25);
    }
    [data-theme="light"] .sudoku-numpad-enhanced button:hover {
      background: linear-gradient(135deg, #6d28d9, #7c3aed);
      color: white;
    }
    @keyframes shake {
      0%, 100% { transform: translateX(0); }
      25% { transform: translateX(-3px); }
      75% { transform: translateX(3px); }
    }

    /* Moved cell animation */
    .cell.just-moved {
      animation: cellBounce 0.3s ease-out;
    }
    @keyframes cellBounce {
      0%   { transform: scale(0.85); }
      60%  { transform: scale(1.08); }
      100% { transform: scale(1); }
    }

    /* Banner */
    .banner {
      margin-top: 14px; padding: 14px 18px; border-radius: var(--radius-md);
      background: rgba(124, 58, 237, 0.1);
      border: 1px solid rgba(124, 58, 237, 0.3);
      color: var(--accent-3); font-size: 0.88rem; font-weight: 600;
      display: none; line-height: 1.5;
      animation: bannerIn 0.4s ease-out;
    }
    .banner.success { background: rgba(16, 185, 129, 0.1); border-color: rgba(16, 185, 129, 0.3); color: var(--emerald); }
    .banner.info    { background: rgba(6, 182, 212, 0.1); border-color: rgba(6, 182, 212, 0.3); color: var(--cyan); }
    @keyframes bannerIn {
      from { opacity: 0; transform: translateY(8px); }
      to   { opacity: 1; transform: translateY(0); }
    }
    .banner .score-display {
      font-size: 1.4rem; font-weight: 800; color: var(--amber);
      display: block; margin-top: 6px; font-family: var(--font-display);
    }
    .banner .rank-display {
      font-size: 0.82rem; color: var(--text-muted);
      display: block; margin-top: 2px;
    }

    /* Controls */
    .btn-new {
      background: rgba(30, 41, 59, 0.7); color: var(--text-muted);
      border: 1px solid var(--border);
      padding: 9px 18px; border-radius: var(--radius-sm);
      cursor: pointer; font-size: 0.85rem; font-weight: 600;
      transition: all var(--transition-fast);
      font-family: var(--font-body);
    }
    .btn-new:hover { background: rgba(40, 53, 72, 0.8); color: var(--text); border-color: var(--border-glow); }

    .sudoku-numpad {
      display: flex; gap: 6px; justify-content: center; flex-wrap: wrap;
      margin-top: 10px;
    }
    .sudoku-numpad button {
      width: 40px; height: 40px; border-radius: var(--radius-sm);
      border: 1px solid var(--border);
      background: rgba(30, 41, 59, 0.7);
      color: var(--text); font-size: 1rem; font-weight: 600;
      cursor: pointer; transition: all var(--transition-fast);
      font-family: var(--font-body);
    }
    .sudoku-numpad button:hover { background: var(--accent-1); border-color: var(--accent-1); }

    #extra-controls p {
      color: var(--text-dim); font-size: 0.75rem; margin: 6px 0 0; 
    }

    /* ======================================================================
       CONFETTI CANVAS
       ====================================================================== */
    #confetti-canvas {
      position: fixed; inset: 0; z-index: 300; pointer-events: none;
    }

    /* ======================================================================
       FOOTER
       ====================================================================== */
    .footer {
      margin-top: 48px; text-align: center;
      color: var(--text-dim); font-size: 0.78rem;
    }
    .footer a { color: var(--accent-3); text-decoration: none; }
    .footer a:hover { text-decoration: underline; }

    /* ======================================================================
       KEYBOARD HINT
       ====================================================================== */
    .kb-hint {
      display: inline-flex; align-items: center; gap: 6px;
      margin-top: 6px; padding: 4px 10px;
      background: rgba(15, 23, 48, 0.6); border-radius: 6px;
      font-size: 0.7rem; color: var(--text-dim);
    }
    kbd {
      display: inline-flex; align-items: center; justify-content: center;
      min-width: 22px; height: 20px; padding: 0 5px;
      background: rgba(30, 41, 59, 0.8); border: 1px solid var(--border);
      border-radius: 4px; font-size: 0.68rem; font-weight: 700;
      color: var(--text-muted); font-family: var(--font-body);
    }

    /* Dungeon Survival Cell Details */
    .cell.dungeon-cell {
      width: 62px; height: 60px;
      flex-direction: column;
      gap: 3px;
      padding: 4px 2px;
    }
    .cell.dungeon-cell .ds-emoji {
      font-size: 1.15rem;
      line-height: 1;
    }
    .cell.dungeon-cell .ds-val {
      font-size: 0.68rem;
      font-weight: 700;
      line-height: 1;
      letter-spacing: -0.01em;
    }
    .cell.dungeon-cell .ds-val.hp-req {
      color: var(--rose);
    }
    .cell.dungeon-cell .ds-val.hp-gain {
      color: var(--emerald);
    }

    /* Light Theme Component Surfaces */
    [data-theme="light"] .bg-orb { opacity: 0.16; }
    [data-theme="light"] .bg-stars { opacity: 0.2; filter: invert(1); }
    [data-theme="light"] header h1 {
      background: linear-gradient(135deg, #4f46e5 0%, #7c3aed 40%, #db2777 75%, #4f46e5 100%);
      background-size: 200% 200%;
      -webkit-background-clip: text; background-clip: text;
      -webkit-text-fill-color: transparent;
    }
    [data-theme="light"] .lb-overlay { background: rgba(15, 23, 42, 0.35); }
    [data-theme="light"] .lb-tabs,
    [data-theme="light"] .diff-selector { background: rgba(226, 232, 240, 0.85); }
    [data-theme="light"] .lb-close,
    [data-theme="light"] .close-btn { background: rgba(226, 232, 240, 0.9); color: var(--text-muted); }
    [data-theme="light"] .modal-backdrop { background: rgba(15, 23, 42, 0.45); }
    [data-theme="light"] .status-bar { background: rgba(241, 245, 249, 0.9); }
    [data-theme="light"] .board { background: rgba(226, 232, 240, 0.75); }
    [data-theme="light"] .cell {
      background: rgba(255, 255, 255, 0.92);
      border-color: rgba(148, 163, 184, 0.22);
      color: var(--text);
    }
    [data-theme="light"] .cell:hover { background: #ffffff; }
    [data-theme="light"] .cell.player { background: rgba(124, 58, 237, 0.18); border-color: var(--accent-2); }
    [data-theme="light"] .cell.valid { background: rgba(16, 185, 129, 0.16); border-color: var(--emerald); }
    [data-theme="light"] .cell.wall,
    [data-theme="light"] .cell.thorn { background: rgba(203, 213, 225, 0.85); }
    [data-theme="light"] .cell.white-sq { background: #ffffff; color: #0f172a; }
    [data-theme="light"] .cell.black-sq { background: #334155; color: #f8fafc; }
    [data-theme="light"] .cell.sudoku-given { background: rgba(226, 232, 240, 0.9); color: var(--accent-1); }
    [data-theme="light"] .cell.sudoku-empty { background: #ffffff; color: var(--emerald); }
    [data-theme="light"] .btn-new,
    [data-theme="light"] .sudoku-numpad button,
    [data-theme="light"] .sudoku-numpad-enhanced button { background: rgba(226, 232, 240, 0.8); color: var(--text); }
    [data-theme="light"] .btn-new:hover { background: rgba(203, 213, 225, 0.95); }
    [data-theme="light"] .sudoku-numpad button:hover { background: var(--accent-1); color: white; }
    [data-theme="light"] .kb-hint { background: rgba(226, 232, 240, 0.75); }
    [data-theme="light"] kbd { background: #ffffff; color: var(--text); }
  </style>
</head>
<body>

  <!-- Animated Background -->
  <div class="bg-canvas">
    <div class="bg-orb"></div>
    <div class="bg-orb"></div>
    <div class="bg-orb"></div>
    <div class="bg-stars"></div>
  </div>

  <!-- Confetti Canvas -->
  <canvas id="confetti-canvas"></canvas>

  <div class="app">
    <!-- Top Stats Bar -->
    <div class="top-bar">
      <div class="top-bar-stats">
        <div class="stat-chip"><span class="icon">🏆</span> Total: <span class="val" id="total-score">0</span></div>
        <div class="stat-chip"><span class="icon">⭐</span> Rank: <span class="val" id="player-rank">Beginner</span></div>
        <div class="stat-chip"><span class="icon">🎮</span> Played: <span class="val" id="games-played">0</span></div>
      </div>
      <div style="display:flex;gap:8px;align-items:center;">
        <button class="theme-switch" id="btn-theme" onclick="toggleTheme()" title="Toggle Dark / Light Theme" aria-label="Toggle Theme">
          <span class="ts-icon">🌙</span>
          <span class="ts-icon">☀️</span>
          <span class="ts-thumb" id="theme-thumb">🌙</span>
        </button>
        <button class="btn-sound" id="btn-sound" onclick="toggleSound()" title="Toggle Sound">🔊</button>
        <button class="btn-leaderboard" onclick="openLeaderboard()">🏅 Leaderboard</button>
      </div>
    </div>

    <!-- Header -->
    <header>
      <h1>🧠 Brain Tester</h1>
      <p class="tagline">Master <span>Data Structures & Algorithms</span> through Play</p>
    </header>

    <!-- Game Cards -->
    <div class="grid-cards" id="grid-cards">
      <div class="card" id="card-keyhunter">
        <div>
          <div class="card-icon">🗝️</div>
          <h3>Key Hunter</h3>
          <div class="algo-tag">BFS + Bitmasking</div>
          <p class="card-desc">Navigate the maze, collect all keys to unlock doors. Find the shortest path!</p>
        </div>
        <div class="card-footer">
          <span class="card-best" id="best-keyhunter"></span>
          <button class="btn-play" onclick="openGame('keyhunter')">▶ Play</button>
        </div>
      </div>
      <div class="card" id="card-dungeon">
        <div>
          <div class="card-icon">🛡️</div>
          <h3>Dungeon Survival</h3>
          <div class="algo-tag">Dynamic Programming</div>
          <p class="card-desc">Rescue the princess with minimum starting health. Plan your path wisely!</p>
        </div>
        <div class="card-footer">
          <span class="card-best" id="best-dungeon"></span>
          <button class="btn-play" onclick="openGame('dungeon')">▶ Play</button>
        </div>
      </div>
      <div class="card" id="card-dualrobot">
        <div>
          <div class="card-icon">🤖</div>
          <h3>Dual Robot Challenge</h3>
          <div class="algo-tag">Dynamic Programming</div>
          <p class="card-desc">Control two robots simultaneously to maximize loot collection!</p>
        </div>
        <div class="card-footer">
          <span class="card-best" id="best-dualrobot"></span>
          <button class="btn-play" onclick="openGame('dualrobot')">▶ Play</button>
        </div>
      </div>
      <div class="card" id="card-cherry">
        <div>
          <div class="card-icon">🍒</div>
          <h3>Cherry Expedition</h3>
          <div class="algo-tag">Dynamic Programming</div>
          <p class="card-desc">Collect maximum cherries on a round trip. Each cherry disappears once taken!</p>
        </div>
        <div class="card-footer">
          <span class="card-best" id="best-cherry"></span>
          <button class="btn-play" onclick="openGame('cherry')">▶ Play</button>
        </div>
      </div>
      <div class="card" id="card-permutation">
        <div>
          <div class="card-icon">🧩</div>
          <h3>Permutation Puzzle</h3>
          <div class="algo-tag">Greedy Approach</div>
          <p class="card-desc">Transform the board into a perfect chessboard pattern with minimal swaps!</p>
        </div>
        <div class="card-footer">
          <span class="card-best" id="best-permutation"></span>
          <button class="btn-play" onclick="openGame('permutation')">▶ Play</button>
        </div>
      </div>
      <div class="card" id="card-sudoku">
        <div>
          <div class="card-icon">🔢</div>
          <h3>Sudoku Master</h3>
          <div class="algo-tag">Backtracking + Recursion</div>
          <p class="card-desc">Classic 9×9 challenge. Fill every row, column, and box with digits 1–9!</p>
        </div>
        <div class="card-footer">
          <span class="card-best" id="best-sudoku"></span>
          <button class="btn-play" onclick="openGame('sudoku')">▶ Play</button>
        </div>
      </div>
    </div>

    <div class="footer">
      <p>Built with C++ & vanilla JS — zero frameworks, zero dependencies</p>
    </div>
  </div>

  <!-- Leaderboard Panel -->
  <div class="lb-overlay" id="lb-overlay" onclick="closeLBIfOutside(event)">
    <div class="lb-panel" id="lb-panel">
      <button class="lb-close" onclick="closeLeaderboard()">✕</button>
      <h2>🏅 Leaderboard</h2>
      <p class="lb-subtitle">Your personal best scores across all games</p>
      <div class="lb-tabs" id="lb-tabs"></div>
      <div id="lb-content"></div>
      <button class="btn-clear-lb" onclick="clearScores()">🗑️ Clear All Scores</button>
    </div>
  </div>

  <!-- Game Modal -->
  <div class="modal-backdrop" id="modal">
    <div class="modal" onclick="event.stopPropagation()">
      <button class="close-btn" onclick="closeModal()">✕</button>
      <div class="modal-header">
        <h3 id="modal-title"></h3>
        <p id="modal-desc"></p>
      </div>
      <div class="diff-selector" id="diff-selector">
        <button class="diff-btn active" onclick="setDiff('easy')">Easy</button>
        <button class="diff-btn" onclick="setDiff('medium')">Medium</button>
        <button class="diff-btn" onclick="setDiff('hard')">Hard</button>
      </div>
      <div class="status-bar" id="status-bar"></div>
      <div class="board" id="board"></div>
      <div id="extra-controls"></div>
      <div style="margin-top:10px;">
        <button class="btn-new" onclick="newPuzzle()">🔄 New Puzzle</button>
      </div>
      <div class="banner" id="banner"></div>
    </div>
  </div>

<script>
// ============================================================================
// SOUND ENGINE (Web Audio API — no external files)
// ============================================================================
let audioCtx = null;
let soundEnabled = true;

function initAudio() {
  if (!audioCtx) {
    try { audioCtx = new (window.AudioContext || window.webkitAudioContext)(); }
    catch(e) { soundEnabled = false; }
  }
}

function playTone(freq, duration, type = 'sine', vol = 0.12) {
  if (!soundEnabled || !audioCtx) return;
  try {
    const osc = audioCtx.createOscillator();
    const gain = audioCtx.createGain();
    osc.type = type;
    osc.frequency.setValueAtTime(freq, audioCtx.currentTime);
    gain.gain.setValueAtTime(vol, audioCtx.currentTime);
    gain.gain.exponentialRampToValueAtTime(0.001, audioCtx.currentTime + duration);
    osc.connect(gain);
    gain.connect(audioCtx.destination);
    osc.start();
    osc.stop(audioCtx.currentTime + duration);
  } catch(e) {}
}

function sfxClick()   { playTone(800, 0.08, 'sine', 0.08); }
function sfxMove()    { playTone(520, 0.1, 'triangle', 0.06); }
function sfxKey()     { playTone(1200, 0.15, 'sine', 0.1); playTone(1600, 0.15, 'sine', 0.08); }
function sfxError()   { playTone(200, 0.2, 'sawtooth', 0.08); }
function sfxSuccess() {
  playTone(523, 0.15, 'sine', 0.1);
  setTimeout(() => playTone(659, 0.15, 'sine', 0.1), 100);
  setTimeout(() => playTone(784, 0.15, 'sine', 0.1), 200);
  setTimeout(() => playTone(1047, 0.3, 'sine', 0.12), 300);
}

function toggleSound() {
  initAudio();
  soundEnabled = !soundEnabled;
  document.getElementById('btn-sound').textContent = soundEnabled ? '🔊' : '🔇';
  if (soundEnabled) sfxClick();
}

let currentTheme = 'dark';
function applyTheme(theme) {
  currentTheme = theme === 'light' ? 'light' : 'dark';
  if (currentTheme === 'light') {
    document.documentElement.setAttribute('data-theme', 'light');
  } else {
    document.documentElement.removeAttribute('data-theme');
  }
  const thumb = document.getElementById('theme-thumb');
  if (thumb) thumb.textContent = currentTheme === 'light' ? '☀️' : '🌙';
}

function toggleTheme() {
  initAudio();
  sfxClick();
  const next = currentTheme === 'dark' ? 'light' : 'dark';
  applyTheme(next);
  try { localStorage.setItem('brainTesterTheme', next); } catch(e) {}
}

try {
  const savedTheme = localStorage.getItem('brainTesterTheme');
  if (savedTheme === 'light' || savedTheme === 'dark') applyTheme(savedTheme);
} catch(e) {}

// ============================================================================
// CONFETTI ENGINE
// ============================================================================
function launchConfetti() {
  const canvas = document.getElementById('confetti-canvas');
  const ctx = canvas.getContext('2d');
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;

  const particles = [];
  const colors = ['#7c3aed','#a855f7','#06b6d4','#10b981','#f59e0b','#f43f5e','#818cf8','#fbbf24'];
  for (let i = 0; i < 120; i++) {
    particles.push({
      x: canvas.width / 2 + (Math.random() - 0.5) * 200,
      y: canvas.height / 2,
      vx: (Math.random() - 0.5) * 16,
      vy: -Math.random() * 18 - 4,
      w: Math.random() * 8 + 4,
      h: Math.random() * 4 + 2,
      color: colors[Math.floor(Math.random() * colors.length)],
      rot: Math.random() * Math.PI * 2,
      rotV: (Math.random() - 0.5) * 0.3,
      life: 1,
    });
  }

  let frame = 0;
  function animate() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    let alive = false;
    for (const p of particles) {
      if (p.life <= 0) continue;
      alive = true;
      p.x += p.vx;
      p.y += p.vy;
      p.vy += 0.35;
      p.rot += p.rotV;
      p.life -= 0.008;
      ctx.save();
      ctx.translate(p.x, p.y);
      ctx.rotate(p.rot);
      ctx.globalAlpha = Math.max(0, p.life);
      ctx.fillStyle = p.color;
      ctx.fillRect(-p.w / 2, -p.h / 2, p.w, p.h);
      ctx.restore();
    }
    if (alive && frame < 300) { frame++; requestAnimationFrame(animate); }
    else { ctx.clearRect(0, 0, canvas.width, canvas.height); }
  }
  animate();
}

// ============================================================================
// PERSISTENT SCORING (localStorage)
// ============================================================================
function loadScores() {
  try { return JSON.parse(localStorage.getItem('brainTesterScores') || '[]'); } catch { return []; }
}
function saveScore(entry) {
  const scores = loadScores();
  scores.push(entry);
  localStorage.setItem('brainTesterScores', JSON.stringify(scores));
  updateStatsBar();
}
function clearScores() {
  if (confirm('Clear all scores? This cannot be undone.')) {
    localStorage.removeItem('brainTesterScores');
    updateStatsBar();
    renderLeaderboard();
  }
}
function getTotalScore() { return loadScores().reduce((a, s) => a + s.score, 0); }
function getGamesPlayed() { return loadScores().length; }
function getRank(total) {
  if (total >= 10000) return 'DSA Legend';
  if (total >= 8000)  return 'Master';
  if (total >= 6000)  return 'Algorithmist';
  if (total >= 4000)  return 'Challenger';
  if (total >= 2000)  return 'Explorer';
  return 'Beginner';
}
function getBestScore(game) {
  const scores = loadScores().filter(s => s.game === game);
  if (!scores.length) return null;
  return Math.max(...scores.map(s => s.score));
}
function updateStatsBar() {
  const total = getTotalScore();
  document.getElementById('total-score').textContent = total.toLocaleString();
  document.getElementById('player-rank').textContent = getRank(total);
  document.getElementById('games-played').textContent = getGamesPlayed();
  // Update card best scores
  for (const g of ['keyhunter','dungeon','dualrobot','cherry','permutation','sudoku']) {
    const best = getBestScore(g);
    const el = document.getElementById(`best-${g}`);
    if (el) el.innerHTML = best ? `Best: <b>${best}</b>` : '';
  }
}

// ============================================================================
// LEADERBOARD
// ============================================================================
let lbFilter = 'all';
function openLeaderboard() {
  sfxClick();
  document.getElementById('lb-overlay').classList.add('open');
  renderLeaderboard();
}
function closeLeaderboard() { document.getElementById('lb-overlay').classList.remove('open'); }
function closeLBIfOutside(e) { if (e.target === document.getElementById('lb-overlay')) closeLeaderboard(); }

function renderLeaderboard() {
  const tabs = document.getElementById('lb-tabs');
  const gameNames = {all:'All',keyhunter:'Key Hunter',dungeon:'Dungeon',dualrobot:'Dual Robot',cherry:'Cherry',permutation:'Permutation',sudoku:'Sudoku'};
  tabs.innerHTML = '';
  for (const [key, name] of Object.entries(gameNames)) {
    const btn = document.createElement('button');
    btn.className = 'lb-tab' + (lbFilter === key ? ' active' : '');
    btn.textContent = name;
    btn.onclick = () => { lbFilter = key; renderLeaderboard(); };
    tabs.appendChild(btn);
  }

  let scores = loadScores();
  if (lbFilter !== 'all') scores = scores.filter(s => s.game === lbFilter);
  scores.sort((a, b) => b.score - a.score);
  scores = scores.slice(0, 20);

  const content = document.getElementById('lb-content');
  if (!scores.length) {
    content.innerHTML = '<div class="lb-empty">🎮 No scores yet. Play some games!</div>';
    return;
  }

  const gameIcons = {keyhunter:'🗝️',dungeon:'🛡️',dualrobot:'🤖',cherry:'🍒',permutation:'🧩',sudoku:'🔢'};
  content.innerHTML = scores.map((s, i) => {
    const rankClass = i === 0 ? 'gold' : i === 1 ? 'silver' : i === 2 ? 'bronze' : '';
    const diffLabel = s.diff.charAt(0).toUpperCase() + s.diff.slice(1);
    const timeStr = s.time ? `${s.time.toFixed(1)}s` : '';
    return `<div class="lb-entry">
      <div class="lb-rank ${rankClass}">${i + 1}</div>
      <div class="lb-info">
        <div class="lb-game">${gameIcons[s.game] || ''} ${s.gameName || s.game}</div>
        <div class="lb-meta">${diffLabel} · ${timeStr}</div>
      </div>
      <div class="lb-score">${s.score}</div>
    </div>`;
  }).join('');
}

// ============================================================================
// TIMER
// ============================================================================
let timerStart = 0;
let timerInterval = null;
function startTimer() {
  timerStart = Date.now();
  clearInterval(timerInterval);
  timerInterval = setInterval(() => {
    const el = document.getElementById('timer-val');
    if (el) el.textContent = getElapsed().toFixed(1) + 's';
  }, 100);
}
function stopTimer() { clearInterval(timerInterval); }
function getElapsed() { return (Date.now() - timerStart) / 1000; }

// ============================================================================
// SHARED GAME STATE
// ============================================================================
let currentGame = '';
let currentDiff = 'easy';
let gameData = {};
let S = {};

function openGame(game) {
  initAudio();
  sfxClick();
  currentGame = game;
  document.getElementById('modal').classList.add('open');
  setDiff('easy');
}

function closeModal() {
  sfxClick();
  stopTimer();
  document.getElementById('modal').classList.remove('open');
}

function setDiff(d) {
  sfxClick();
  currentDiff = d;
  document.querySelectorAll('.diff-btn').forEach(b => {
    b.classList.toggle('active', b.textContent.toLowerCase() === d);
  });
  newPuzzle();
}

async function newPuzzle() {
  document.getElementById('banner').style.display = 'none';
  try {
    const resp = await fetch(`/api/generate?game=${currentGame}&diff=${currentDiff}`);
    gameData = await resp.json();
  } catch (e) {
    console.error('API error:', e);
    return;
  }
  S = {};
  startTimer();
  setupGame();
}

// ============================================================================
// GAME CONFIG
// ============================================================================
const GAMES = {
  keyhunter: {
    icon: '🗝️', title: 'Key Hunter', name: 'Key Hunter',
    desc: 'Move through the maze with arrow keys or clicks. Collect all keys 🔑 to unlock doors 🔒. Reach all keys in fewest steps!',
  },
  dungeon: {
    icon: '🛡️', title: 'Dungeon Survival', name: 'Dungeon Survival',
    desc: 'Navigate from ⚔️ to 👑 (right/down only). 😈 drain HP, 🧪 restore HP. Find the path needing minimum starting HP!',
  },
  dualrobot: {
    icon: '🤖', title: 'Dual Robot Challenge', name: 'Dual Robot',
    desc: 'Two robots move down one row per turn. Pick a column for each robot (left/stay/right). Same cell = counted once. Maximize loot!',
  },
  cherry: {
    icon: '🍒', title: 'Cherry Expedition', name: 'Cherry Expedition',
    desc: 'Go (0,0)→(N-1,N-1)→(0,0). Move ➡️⬇️ going, ⬅️⬆️ returning. 🍒=cherry, 🌿=empty, 🌵=blocked. Max cherries!',
  },
  permutation: {
    icon: '🧩', title: 'Permutation Puzzle', name: 'Permutation Puzzle',
    desc: 'Transform into a chessboard pattern. Click two row/column headers to swap them. Minimize total swaps!',
  },
  sudoku: {
    icon: '🔢', title: 'Sudoku Master', name: 'Sudoku Master',
    desc: 'Fill the 9×9 grid so each row, column, and 3×3 box has 1–9. Click a cell, then pick a number. Use keyboard 1-9 too!',
  },
};

function setupGame() {
  const g = GAMES[currentGame];
  document.getElementById('modal-title').textContent = g.icon + ' ' + g.title;
  document.getElementById('modal-desc').textContent = g.desc;
  // Reset board class for non-sudoku games
  document.getElementById('board').className = 'board';
  switch (currentGame) {
    case 'keyhunter':   setupKeyHunter(); break;
    case 'dungeon':     setupDungeon(); break;
    case 'dualrobot':   setupDualRobot(); break;
    case 'cherry':      setupCherry(); break;
    case 'permutation': setupPermutation(); break;
    case 'sudoku':      setupSudoku(); break;
  }
}

function showBanner(msg, type = 'success') {
  const b = document.getElementById('banner');
  b.className = 'banner ' + type;
  b.style.display = 'block';
  b.innerHTML = msg;
}

async function finishGame(opts) {
  stopTimer();
  sfxSuccess();
  launchConfetti();
  const elapsed = getElapsed();
  const diffMap = { easy: '1', medium: '2', hard: '3' };
  try {
    const resp = await fetch(`/api/score?diff=${diffMap[currentDiff] || '1'}&optimal=${opts.optimal ? '1' : '0'}&wrong=${opts.wrong || 0}&seconds=${elapsed.toFixed(1)}`);
    const data = await resp.json();
    const g = GAMES[currentGame];
    saveScore({ game: currentGame, gameName: g.name, diff: currentDiff, score: data.score, time: elapsed, date: Date.now() });
    showBanner(`${opts.message}<span class="score-display">+${data.score} pts</span><span class="rank-display">Rank: ${data.rank} · Time: ${elapsed.toFixed(1)}s</span>`, 'success');
  } catch {
    showBanner(opts.message, 'success');
  }
}

// ============================================================================
// 1. KEY HUNTER
// ============================================================================
function setupKeyHunter() {
  const d = gameData;
  S = { grid: d.grid, rows: d.rows, cols: d.cols, keys: d.keys, optimal: d.optimal,
        pr: 0, pc: 0, steps: 0, collectedKeys: 0, mask: 0, done: false };
  for (let r = 0; r < S.rows; r++)
    for (let c = 0; c < S.cols; c++)
      if (S.grid[r][c] === '@') { S.pr = r; S.pc = c; }
  document.getElementById('status-bar').innerHTML =
    `<span>🗝️ Keys: <b id="kh-keys">0/${S.keys}</b></span>
     <span>👣 Steps: <b id="kh-steps">0</b></span>
     <span>🏆 Optimal: <b id="kh-opt">???</b></span>
     <span class="timer-display">⏱️ <b id="timer-val">0.0s</b></span>`;
  document.getElementById('extra-controls').innerHTML =
    '<div class="kb-hint"><kbd>↑</kbd><kbd>↓</kbd><kbd>←</kbd><kbd>→</kbd> or click green cells</div>';
  renderKeyHunter();
}

function renderKeyHunter() {
  const b = document.getElementById('board');
  b.style.gridTemplateColumns = `repeat(${S.cols}, 52px)`;
  b.innerHTML = '';
  for (let r = 0; r < S.rows; r++) {
    for (let c = 0; c < S.cols; c++) {
      const div = document.createElement('div');
      const ch = S.grid[r][c];
      let cls = 'cell', txt = '';
      if (r === S.pr && c === S.pc) { cls += ' player'; txt = '🧑'; }
      else if (ch === '#') { cls += ' wall'; txt = '🧱'; }
      else if (ch >= 'a' && ch <= 'f') {
        const ki = ch.charCodeAt(0) - 97;
        if (S.mask & (1 << ki)) { txt = '·'; } else { cls += ' key'; txt = '🔑'; }
      }
      else if (ch >= 'A' && ch <= 'F') {
        const ki = ch.charCodeAt(0) - 65;
        if (S.mask & (1 << ki)) { txt = '🚪'; } else { cls += ' lock'; txt = '🔒'; }
      }
      else { txt = '·'; }

      const dr = [-1,1,0,0], dc = [0,0,-1,1];
      for (let i = 0; i < 4; i++) {
        if (r === S.pr + dr[i] && c === S.pc + dc[i] && !S.done) {
          if (ch !== '#') {
            if (ch >= 'A' && ch <= 'F') {
              if (S.mask & (1 << (ch.charCodeAt(0) - 65))) cls += ' valid';
            } else { cls += ' valid'; }
          }
        }
      }
      div.className = cls;
      div.textContent = txt;
      if (cls.includes('valid')) {
        const rr = r, cc = c;
        div.onclick = () => moveKeyHunter(rr, cc);
      }
      b.appendChild(div);
    }
  }
  document.getElementById('kh-keys').textContent = `${S.collectedKeys}/${S.keys}`;
  document.getElementById('kh-steps').textContent = S.steps;
}

function moveKeyHunter(r, c) {
  if (S.done) return;
  sfxMove();
  S.pr = r; S.pc = c; S.steps++;
  const ch = S.grid[r][c];
  if (ch >= 'a' && ch <= 'f') {
    const ki = ch.charCodeAt(0) - 97;
    if (!(S.mask & (1 << ki))) { S.mask |= (1 << ki); S.collectedKeys++; sfxKey(); }
  }
  renderKeyHunter();
  if (S.collectedKeys === S.keys) {
    S.done = true;
    document.getElementById('kh-opt').textContent = S.optimal;
    const isOptimal = S.steps <= S.optimal;
    finishGame({ optimal: isOptimal, wrong: Math.max(0, S.steps - S.optimal), message:
      `🎉 All keys collected in ${S.steps} steps! Optimal: ${S.optimal} steps.${isOptimal ? ' ⭐ Perfect!' : ''}` });
  }
}

// ============================================================================
// 2. DUNGEON SURVIVAL
// ============================================================================
function setupDungeon() {
  const d = gameData;
  S = { grid: d.grid, rows: d.rows, cols: d.cols, optimal: d.optimal,
        pr: 0, pc: 0, curHP: d.grid[0][0], minPeak: Math.max(1, 1 - d.grid[0][0]), done: false };
  document.getElementById('status-bar').innerHTML =
    `<span>⚔️ Position: <b id="ds-pos">(0,0)</b></span>
     <span>🛡️ Min HP: <b id="ds-hp">${S.minPeak}</b></span>
     <span>🏆 Optimal: <b id="ds-opt">???</b></span>
     <span class="timer-display">⏱️ <b id="timer-val">0.0s</b></span>`;
  document.getElementById('extra-controls').innerHTML =
    '<div class="kb-hint"><kbd>→</kbd><kbd>↓</kbd> or click green cells to move</div>';
  renderDungeon();
}

function renderDungeon() {
  document.getElementById('ds-pos').textContent = `(${S.pr},${S.pc})`;
  document.getElementById('ds-hp').textContent = S.minPeak;
  const b = document.getElementById('board');
  b.style.gridTemplateColumns = `repeat(${S.cols}, 62px)`;
  b.innerHTML = '';
  for (let r = 0; r < S.rows; r++) {
    for (let c = 0; c < S.cols; c++) {
      const div = document.createElement('div');
      const v = S.grid[r][c];
      const isValid = !S.done && ((r === S.pr + 1 && c === S.pc) || (r === S.pr && c === S.pc + 1));
      div.className = 'cell dungeon-cell' + (isValid ? ' valid' : '');
      let emoji = v < 0 ? '😈' : '🧪';
      if (r === S.pr && c === S.pc) { emoji = '⚔️'; div.classList.add('player'); }
      else if (r === S.rows - 1 && c === S.cols - 1) { emoji = '👑'; }
      const hpText = (v > 0 ? '+' + v : v) + ' HP';
      const hpClass = v < 0 ? 'hp-req' : 'hp-gain';
      div.innerHTML = `<span class="ds-emoji">${emoji}</span><span class="ds-val ${hpClass}">${hpText}</span>`;
      div.title = v < 0 ? `Health Req: ${Math.abs(v)} (${v} HP)` : `Health Gained: +${v} HP`;
      if (isValid) { const rr = r, cc = c; div.onclick = () => stepDungeon(rr, cc); }
      b.appendChild(div);
    }
  }
}

function stepDungeon(r, c) {
  if (S.done) return;
  sfxMove();
  S.pr = r; S.pc = c;
  S.curHP += S.grid[r][c];
  S.minPeak = Math.max(S.minPeak, 1 - S.curHP);
  renderDungeon();
  if (S.pr === S.rows - 1 && S.pc === S.cols - 1) {
    S.done = true;
    document.getElementById('ds-opt').textContent = S.optimal;
    const isOptimal = S.minPeak <= S.optimal;
    const wrong = isOptimal ? 0 : 1;
    finishGame({ optimal: isOptimal, wrong, message:
      `🎉 Path done! You needed ${S.minPeak} HP. Optimal: ${S.optimal} HP.${isOptimal ? ' ⭐ Perfect!' : ''}` });
  }
}

// ============================================================================
// 3. DUAL ROBOT
// ============================================================================
function setupDualRobot() {
  const d = gameData;
  S = { grid: d.grid, rows: d.rows, cols: d.cols, optimal: d.optimal,
        r1: 0, c1: 0, r2: 0, c2: d.cols - 1, row: 0, loot: 0, phase: 'pick1', done: false };
  S.loot = d.grid[0][0] + (0 === d.cols - 1 ? 0 : d.grid[0][d.cols - 1]);
  document.getElementById('status-bar').innerHTML =
    `<span>🤖₁ Col: <b id="dr-c1">0</b></span>
     <span>🤖₂ Col: <b id="dr-c2">${S.c2}</b></span>
     <span>📦 Loot: <b id="dr-loot">${S.loot}</b></span>
     <span>🏆 Optimal: <b id="dr-opt">???</b></span>
     <span class="timer-display">⏱️ <b id="timer-val">0.0s</b></span>`;
  document.getElementById('extra-controls').innerHTML =
    `<p style="color:var(--accent-3);font-size:0.8rem;margin:6px 0 0;font-weight:600;" id="dr-phase-txt">
      ▶ Pick column for Robot 1 (next row)</p>`;
  renderDualRobot();
}

function renderDualRobot() {
  document.getElementById('dr-c1').textContent = S.c1;
  document.getElementById('dr-c2').textContent = S.c2;
  document.getElementById('dr-loot').textContent = S.loot;
  const phaseEl = document.getElementById('dr-phase-txt');
  if (phaseEl) phaseEl.textContent = S.phase === 'pick1' ? '▶ Pick column for Robot 1 (next row)' : '▶ Pick column for Robot 2 (next row)';
  const b = document.getElementById('board');
  b.style.gridTemplateColumns = `repeat(${S.cols}, 52px)`;
  b.innerHTML = '';
  for (let r = 0; r < S.rows; r++) {
    for (let c = 0; c < S.cols; c++) {
      const div = document.createElement('div');
      let cls = 'cell', txt = String(S.grid[r][c]);
      if (r === S.row && c === S.c1) { cls += ' player'; txt = '🤖'; }
      if (r === S.row && c === S.c2) { cls += ' player'; txt = (c === S.c1) ? '🤖🤖' : '🤖'; }
      if (!S.done && r === S.row + 1) {
        if (S.phase === 'pick1') {
          if (c >= S.c1 - 1 && c <= S.c1 + 1 && c >= 0 && c < S.cols) cls += ' valid';
        } else {
          if (c >= S.c2 - 1 && c <= S.c2 + 1 && c >= 0 && c < S.cols) cls += ' valid';
        }
      }
      div.className = cls;
      div.textContent = txt;
      if (cls.includes('valid')) { const cc = c; div.onclick = () => stepDualRobot(cc); }
      b.appendChild(div);
    }
  }
}

function stepDualRobot(c) {
  if (S.done) return;
  sfxMove();
  if (S.phase === 'pick1') {
    S.nextC1 = c;
    S.phase = 'pick2';
    renderDualRobot();
  } else {
    const nc1 = S.nextC1, nc2 = c;
    S.row++; S.c1 = nc1; S.c2 = nc2;
    const collected = (S.c1 === S.c2) ? S.grid[S.row][S.c1] : (S.grid[S.row][S.c1] + S.grid[S.row][S.c2]);
    S.loot += collected;
    S.phase = 'pick1';
    renderDualRobot();
    if (S.row === S.rows - 1) {
      S.done = true;
      document.getElementById('dr-opt').textContent = S.optimal;
      const isOptimal = S.loot >= S.optimal;
      finishGame({ optimal: isOptimal, wrong: isOptimal ? 0 : 1, message:
        `🎉 Total loot: ${S.loot}. Optimal: ${S.optimal}.${isOptimal ? ' ⭐ Perfect!' : ''}` });
    }
  }
}

// ============================================================================
// 4. CHERRY EXPEDITION
// ============================================================================
function setupCherry() {
  const d = gameData;
  const N = d.size;
  S = { grid: d.grid.map(r => [...r]), N, optimal: d.optimal, pr: 0, pc: 0,
        cherries: 0, returning: false, done: false };
  if (d.grid[0][0] === 1) { S.cherries = 1; S.grid[0][0] = 0; }
  document.getElementById('status-bar').innerHTML =
    `<span>📍 Pos: <b id="ch-pos">(0,0)</b></span>
     <span>🍒 Collected: <b id="ch-cher">${S.cherries}</b></span>
     <span>🔄 Phase: <b id="ch-phase">Going →</b></span>
     <span>🏆 Optimal: <b id="ch-opt">???</b></span>
     <span class="timer-display">⏱️ <b id="timer-val">0.0s</b></span>`;
  document.getElementById('extra-controls').innerHTML =
    '<div class="kb-hint"><kbd>→</kbd><kbd>↓</kbd> going · <kbd>←</kbd><kbd>↑</kbd> returning</div>';
  renderCherry();
}

function renderCherry() {
  const N = S.N;
  document.getElementById('ch-pos').textContent = `(${S.pr},${S.pc})`;
  document.getElementById('ch-cher').textContent = S.cherries;
  document.getElementById('ch-phase').textContent = S.returning ? '← Returning' : 'Going →';
  const b = document.getElementById('board');
  b.style.gridTemplateColumns = `repeat(${N}, 52px)`;
  b.innerHTML = '';
  for (let r = 0; r < N; r++) {
    for (let c = 0; c < N; c++) {
      const div = document.createElement('div');
      const v = S.grid[r][c];
      let cls = 'cell', txt = '';
      if (r === S.pr && c === S.pc) { cls += ' player'; txt = '🧑'; }
      else if (v === -1) { cls += ' thorn'; txt = '🌵'; }
      else if (v === 1) { cls += ' cherry'; txt = '🍒'; }
      else { txt = '🌿'; }

      if (!S.done) {
        let validMoves = S.returning
          ? [[S.pr-1, S.pc], [S.pr, S.pc-1]]
          : [[S.pr+1, S.pc], [S.pr, S.pc+1]];
        for (const [vr, vc] of validMoves) {
          if (r === vr && c === vc && vr >= 0 && vr < N && vc >= 0 && vc < N && S.grid[vr][vc] !== -1) {
            cls += ' valid';
          }
        }
      }
      div.className = cls;
      div.textContent = txt;
      if (cls.includes('valid')) { const rr = r, cc = c; div.onclick = () => stepCherry(rr, cc); }
      b.appendChild(div);
    }
  }
}

function stepCherry(r, c) {
  if (S.done) return;
  sfxMove();
  S.pr = r; S.pc = c;
  if (S.grid[r][c] === 1) { S.cherries++; S.grid[r][c] = 0; sfxKey(); }
  if (!S.returning && r === S.N - 1 && c === S.N - 1) S.returning = true;
  if (S.returning && r === 0 && c === 0) {
    S.done = true;
    document.getElementById('ch-opt').textContent = S.optimal;
    const isOptimal = S.cherries >= S.optimal;
    finishGame({ optimal: isOptimal, wrong: isOptimal ? 0 : 1, message:
      `🎉 Round trip done! Cherries: ${S.cherries}. Optimal: ${S.optimal}.${isOptimal ? ' ⭐ Perfect!' : ''}` });
  }
  renderCherry();
}

// ============================================================================
// 5. PERMUTATION PUZZLE
// ============================================================================
function setupPermutation() {
  const d = gameData;
  const N = d.size;
  S = { board: d.grid.map(r => [...r]), N, optimal: d.optimal, swaps: 0,
        selected: null, mode: 'row', done: false };
  document.getElementById('status-bar').innerHTML =
    `<span>🔄 Swaps: <b id="pp-swaps">0</b></span>
     <span>🏆 Optimal: <b id="pp-opt">???</b></span>
     <span class="timer-display">⏱️ <b id="timer-val">0.0s</b></span>`;
  document.getElementById('extra-controls').innerHTML =
    `<div style="margin-top:8px;display:flex;gap:6px;justify-content:center;">
       <button class="btn-new" id="pp-row-btn" onclick="setPPMode('row')" style="background:var(--accent-1);color:white;border-color:var(--accent-1);">Swap Rows</button>
       <button class="btn-new" id="pp-col-btn" onclick="setPPMode('col')">Swap Columns</button>
     </div>
     <p>Click two row/column headers to swap them.</p>`;
  renderPermutation();
}

function setPPMode(m) {
  sfxClick();
  S.mode = m; S.selected = null;
  const rb = document.getElementById('pp-row-btn'), cb = document.getElementById('pp-col-btn');
  rb.style.background = m === 'row' ? 'var(--accent-1)' : '';
  rb.style.color = m === 'row' ? 'white' : '';
  rb.style.borderColor = m === 'row' ? 'var(--accent-1)' : '';
  cb.style.background = m === 'col' ? 'var(--accent-1)' : '';
  cb.style.color = m === 'col' ? 'white' : '';
  cb.style.borderColor = m === 'col' ? 'var(--accent-1)' : '';
  renderPermutation();
}

function renderPermutation() {
  const N = S.N;
  document.getElementById('pp-swaps').textContent = S.swaps;
  const b = document.getElementById('board');
  b.style.gridTemplateColumns = `repeat(${N + 1}, 52px)`;
  b.innerHTML = '';
  // corner
  const corner = document.createElement('div');
  corner.className = 'cell';
  corner.style.background = 'transparent'; corner.style.border = 'none';
  b.appendChild(corner);
  // col headers
  for (let c = 0; c < N; c++) {
    const hdr = document.createElement('div');
    hdr.className = 'cell';
    hdr.textContent = `C${c}`;
    hdr.style.fontSize = '0.7rem';
    if (S.mode === 'col') {
      hdr.style.cursor = 'pointer';
      if (S.selected === c) hdr.classList.add('selected-cell');
      const cc = c;
      hdr.onclick = () => pickPermutation(cc);
    }
    b.appendChild(hdr);
  }
  for (let r = 0; r < N; r++) {
    const rh = document.createElement('div');
    rh.className = 'cell';
    rh.textContent = `R${r}`;
    rh.style.fontSize = '0.7rem';
    if (S.mode === 'row') {
      rh.style.cursor = 'pointer';
      if (S.selected === r) rh.classList.add('selected-cell');
      const rr = r;
      rh.onclick = () => pickPermutation(rr);
    }
    b.appendChild(rh);
    for (let c = 0; c < N; c++) {
      const div = document.createElement('div');
      div.className = 'cell ' + (S.board[r][c] === 0 ? 'white-sq' : 'black-sq');
      div.textContent = S.board[r][c];
      b.appendChild(div);
    }
  }
}

function pickPermutation(idx) {
  if (S.done) return;
  sfxClick();
  if (S.selected === null) {
    S.selected = idx;
    renderPermutation();
  } else {
    const a = S.selected, b2 = idx;
    S.selected = null;
    if (a !== b2) {
      S.swaps++;
      sfxMove();
      if (S.mode === 'row') {
        [S.board[a], S.board[b2]] = [S.board[b2], S.board[a]];
      } else {
        for (let r = 0; r < S.N; r++) {
          [S.board[r][a], S.board[r][b2]] = [S.board[r][b2], S.board[r][a]];
        }
      }
    }
    renderPermutation();
    if (isChessboard(S.board)) {
      S.done = true;
      document.getElementById('pp-opt').textContent = S.optimal;
      const isOptimal = S.swaps <= S.optimal;
      finishGame({ optimal: isOptimal, wrong: Math.max(0, S.swaps - S.optimal), message:
        `🎉 Chessboard achieved in ${S.swaps} swaps! Optimal: ${S.optimal}.${isOptimal ? ' ⭐ Perfect!' : ''}` });
    }
  }
}

function isChessboard(b) {
  const N = b.length;
  let ok1 = true, ok2 = true;
  for (let r = 0; r < N; r++)
    for (let c = 0; c < N; c++) {
      if (b[r][c] !== (r + c) % 2) ok1 = false;
      if (b[r][c] !== (r + c + 1) % 2) ok2 = false;
    }
  return ok1 || ok2;
}

// ============================================================================
// 6. SUDOKU
// ============================================================================
function setupSudoku() {
  const d = gameData;
  S = { puzzle: d.puzzle.map(r => [...r]), solution: d.solution,
        board: d.puzzle.map(r => [...r]), selected: null, done: false, mistakes: 0 };
  document.getElementById('status-bar').innerHTML =
    `<span>✏️ Filled: <b id="su-filled">0</b></span>
     <span>❌ Mistakes: <b id="su-mistakes">0</b></span>
     <span class="timer-display">⏱️ <b id="timer-val">0.0s</b></span>`;
  let html = '<div class="sudoku-numpad-enhanced">';
  for (let n = 1; n <= 9; n++) {
    html += `<button onclick="sudokuNum(${n})">${n}</button>`;
  }
  html += `<button onclick="sudokuNum(0)" style="width:auto;padding:0 16px;font-size:0.85rem;">✕ Clear</button>`;
  html += '</div>';
  html += '<div class="kb-hint" style="margin-top:8px;">Press <kbd>1</kbd>–<kbd>9</kbd> or <kbd>Del</kbd> to fill · <kbd>↑↓←→</kbd> to navigate</div>';
  document.getElementById('extra-controls').innerHTML = html;
  renderSudoku();
}

function renderSudoku() {
  const b = document.getElementById('board');
  b.className = 'board sudoku-board';
  b.style.gridTemplateColumns = `repeat(9, 44px)`;
  b.innerHTML = '';
  let filled = 0, total = 0;
  for (let r = 0; r < 9; r++) {
    for (let c = 0; c < 9; c++) {
      const div = document.createElement('div');
      div.style.width = '44px'; div.style.height = '44px'; div.style.fontSize = '1.1rem';
      const isGiven = S.puzzle[r][c] !== 0;
      const val = S.board[r][c];
      if (isGiven) {
        div.className = 'cell sudoku-given';
        div.textContent = val;
      } else {
        total++;
        div.className = 'cell sudoku-empty';
        div.textContent = val || '';
        if (val) {
          filled++;
          if (val === S.solution[r][c]) div.classList.add('sudoku-correct');
          else div.classList.add('sudoku-wrong');
        }
        if (S.selected && S.selected[0] === r && S.selected[1] === c) {
          div.classList.add('selected-cell');
        }
        const rr = r, cc = c;
        div.onclick = () => { sfxClick(); S.selected = [rr, cc]; renderSudoku(); };
      }
      // 3x3 box borders — high contrast classes
      if ((c + 1) % 3 === 0 && c < 8) div.classList.add('sudoku-border-right');
      if ((r + 1) % 3 === 0 && r < 8) div.classList.add('sudoku-border-bottom');
      b.appendChild(div);
    }
  }
  document.getElementById('su-filled').textContent = `${filled}/${total}`;
  document.getElementById('su-mistakes').textContent = S.mistakes;
}

function sudokuNum(n) {
  if (!S.selected || S.done) return;
  const [r, c] = S.selected;
  if (S.puzzle[r][c] !== 0) return;
  S.board[r][c] = n;
  if (n !== 0 && n !== S.solution[r][c]) { S.mistakes++; sfxError(); }
  else if (n !== 0) { sfxMove(); }
  renderSudoku();
  let complete = true;
  for (let r2 = 0; r2 < 9; r2++)
    for (let c2 = 0; c2 < 9; c2++)
      if (S.board[r2][c2] !== S.solution[r2][c2]) complete = false;
  if (complete) {
    S.done = true;
    finishGame({ optimal: S.mistakes === 0, wrong: S.mistakes, message:
      `🎉 Sudoku solved! Mistakes: ${S.mistakes}.${S.mistakes === 0 ? ' ⭐ Flawless!' : ''}` });
  }
}

// ============================================================================
// KEYBOARD CONTROLS
// ============================================================================
document.addEventListener('keydown', (e) => {
  if (!document.getElementById('modal').classList.contains('open')) return;

  const key = e.key;
  const dirMap = { ArrowUp: [-1,0], ArrowDown: [1,0], ArrowLeft: [0,-1], ArrowRight: [0,1] };

  // Key Hunter keyboard
  if (currentGame === 'keyhunter' && !S.done && dirMap[key]) {
    e.preventDefault();
    const [dr, dc] = dirMap[key];
    const nr = S.pr + dr, nc = S.pc + dc;
    if (nr >= 0 && nr < S.rows && nc >= 0 && nc < S.cols) {
      const ch = S.grid[nr][nc];
      if (ch === '#') return;
      if (ch >= 'A' && ch <= 'F' && !(S.mask & (1 << (ch.charCodeAt(0) - 65)))) return;
      moveKeyHunter(nr, nc);
    }
  }

  // Dungeon keyboard
  if (currentGame === 'dungeon' && !S.done) {
    if (key === 'ArrowRight' && S.pc + 1 < S.cols) { e.preventDefault(); stepDungeon(S.pr, S.pc + 1); }
    if (key === 'ArrowDown' && S.pr + 1 < S.rows)  { e.preventDefault(); stepDungeon(S.pr + 1, S.pc); }
  }

  // Cherry keyboard
  if (currentGame === 'cherry' && !S.done && dirMap[key]) {
    e.preventDefault();
    const [dr, dc] = dirMap[key];
    const nr = S.pr + dr, nc = S.pc + dc;
    if (nr >= 0 && nr < S.N && nc >= 0 && nc < S.N && S.grid[nr][nc] !== -1) {
      if (!S.returning && (dr === 1 || dc === 1) && dr >= 0 && dc >= 0) stepCherry(nr, nc);
      if (S.returning && (dr === -1 || dc === -1) && dr <= 0 && dc <= 0) stepCherry(nr, nc);
    }
  }

  // Sudoku keyboard
  if (currentGame === 'sudoku' && !S.done) {
    if (key >= '1' && key <= '9') { sudokuNum(parseInt(key)); return; }
    if (key === 'Delete' || key === 'Backspace' || key === '0') { sudokuNum(0); return; }
    if (S.selected && dirMap[key]) {
      e.preventDefault();
      const [dr, dc] = dirMap[key];
      let nr = S.selected[0] + dr, nc = S.selected[1] + dc;
      if (nr >= 0 && nr < 9 && nc >= 0 && nc < 9) {
        S.selected = [nr, nc];
        sfxClick();
        renderSudoku();
      }
    }
  }
});

// Close modal on backdrop click
document.getElementById('modal').addEventListener('click', (e) => {
  if (e.target === document.getElementById('modal')) closeModal();
});

// Ripple effect on play buttons
document.querySelectorAll('.btn-play').forEach(btn => {
  btn.addEventListener('click', function(e) {
    const ripple = document.createElement('span');
    ripple.className = 'ripple';
    const rect = this.getBoundingClientRect();
    ripple.style.left = (e.clientX - rect.left) + 'px';
    ripple.style.top = (e.clientY - rect.top) + 'px';
    ripple.style.width = ripple.style.height = Math.max(rect.width, rect.height) + 'px';
    this.appendChild(ripple);
    setTimeout(() => ripple.remove(), 500);
  });
});

// ============================================================================
// INIT
// ============================================================================
updateStatsBar();
</script>
</body>
</html>
)rawliteral";
