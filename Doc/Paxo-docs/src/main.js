import "./style.css";
import "flyonui/flyonui";
import Alpine from "alpinejs";
import { sections } from "./content.js";

function esc(str) {
  return String(str)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;");
}

function codeBlock(code, caption) {
  return `
  <div class="card not-prose border border-base-300 bg-base-100 shadow-sm">
    ${caption ? `<div class="card-body p-3 border-b border-base-300"><h3 class="text-sm font-semibold text-base-content/70 uppercase tracking-wide">${esc(caption)}</h3></div>` : ""}
    <div class="card-body p-0">
      <pre class="p-4 text-sm overflow-x-auto font-mono leading-relaxed"><code>${esc(code)}</code></pre>
    </div>
  </div>`;
}

function badgesHTML(badges) {
  if (!badges || !badges.length) return "";
  return badges
    .map((b) => {
      const [kind, ...rest] = b.split(":");
      const label = rest.length ? rest.join(":") : b;
      const cls = kind.trim() === "new" ? "badge badge-success" : "badge badge-warning";
      return `<span class="${cls} font-medium">${esc(label.trim())}</span>`;
    })
    .join(" ");
}

function notesHTML(notes) {
  if (!notes || !notes.length) return "";
  return notes
    .map((n) => {
      const cls = n.kind === "warn" ? "alert alert-warning" : "alert alert-info";
      const icon =
        n.kind === "warn"
          ? `<span class="icon-[tabler--alert-triangle] size-5 shrink-0"></span>`
          : `<span class="icon-[tabler--info-circle] size-5 shrink-0"></span>`;
      return `<div class="${cls} not-prose">${icon}<span>${n.html}</span></div>`;
    })
    .join("");
}

function sectionHTML(s) {
  const examples = s.examples
    ? s.examples
        .map((e) => codeBlock(e.code, e.caption))
        .join('<div class="h-4"></div>')
    : "";
  return `
    <header class="mb-6">
      <div class="flex items-center gap-3 flex-wrap">
        <h1 class="text-3xl font-extrabold">${esc(s.title)}</h1>
        ${badgesHTML(s.badges)}
      </div>
    </header>
    <div class="prose-paxo">${s.intro || ""}</div>
    ${examples ? `<div class="grid gap-4 mt-6 not-prose">${examples}</div>` : ""}
    ${notesHTML(s.notes)}
  `;
}

document.addEventListener("alpine:init", () => {
  Alpine.data("docs", () => ({
    sections,
    active: sections[0].id,
    query: "",
    theme: "dark",
    mobileOpen: false,

    get filteredNav() {
      const q = this.query.trim().toLowerCase();
      return q
        ? this.sections.filter(
            (s) =>
              s.nav.toLowerCase().includes(q) ||
              (s.title || "").toLowerCase().includes(q) ||
              (s.intro || "").toLowerCase().includes(q)
          )
        : this.sections;
    },

    setActive(id) {
      this.active = id;
      this.mobileOpen = false;
      document.getElementById("main").scrollTo({ top: 0, behavior: "smooth" });
    },

    renderSection(s) {
      return sectionHTML(s);
    },

    setTheme(name) {
      this.theme = name;
      document.documentElement.setAttribute("data-theme", name);
      localStorage.setItem("paxo-theme", name);
    },

    init() {
      const saved = localStorage.getItem("paxo-theme");
      if (saved) this.setTheme(saved);
    },
  }));
});

Alpine.start();
