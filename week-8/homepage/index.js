// declare an array of projects objects
const projects = [
    {
        title: "This Website",
        tags: ["Front End"],
        description: "A responsive portfolio built from scratch using Bootstrap, HTML, and JavaScript to showcase my projects",
        url: "https://who4mos.github.io"
    },
    {
        title: "Hall Of Prophecy",
        tags: ["Python", "SQLite3", "CSV"],
        description: "A program that reads a CSV file, and create a database with multiple tables and relationships, not only one big table as provided. Here i've not used CS50's python library and managed to use sqlite3 python modul for a real-world scenario.",
        url: "https://github.com/who4mos/cs50/tree/main/after-week-7/prophecy"
    },
    {
        title: "Speller",
        tags: ["C", "Data Strucutes"],
        description: "In this problem set i had to implement a hash table in C, for a spell check program.",
        url: "https://github.com/who4mos/cs50/blob/main/week-5/speller/dictionary.c"
    }
];

// select the filter section and create a tag array
const filters = document.querySelector("#filters-column");
let tags = [];

// loop though each project tags and add to tags array
// (if not included already)
for (let i = 0; i < projects.length; i++) {
    const project = projects[i];
    for (let j = 0; j < project["tags"].length; j++) {
        const tag = project["tags"][j];
        if (!tags.includes(tag)) {
            tags.push(tag);
        }
    }
}

// create ALL button and set as active-filter
filters.innerHTML += `<button class="btn btn-filter active-filter" data-filter="all">All</button>`;

// create a button for each tag
for (let i = 0; i < tags.length; i++) {
    let tag = tags[i];
    filters.innerHTML += `<button class="btn btn-filter" data-filter="${tag}">${tag}</button>`;
}

const buttons = document.querySelectorAll("#filters-column .btn-filter");

for (let i = 0; i < buttons.length; i++) {
    buttons[i].addEventListener("click", function() {
        for (let j = 0; j < buttons.length; j++) {
            buttons[j].classList.remove("active-filter");
        }
        
        buttons[i].classList.add("active-filter");

        const tag = buttons[i].getAttribute("data-filter");
        draw_cards(tag);
    });
    
}

// select the row in wich the cards will go in
const row = document.querySelector("#projects-row");

// create a card with each project's content and populate the row
for (let i = 0; i < projects.length; i++) {
    let project_tags = projects[i].tags.join(",");
    let card_content = `<div class="col-md-4 project-card" data-tags="${project_tags}">
    <div class="card text-bg-dark border h-100">
    <div class="card-body d-flex flex-column">
    <h2 class="card-title fs-4">${projects[i]["title"]}</h2>
    <div class="mb-3 d-flex gap-1">`;

    // loop through tags/badges
    for (let j = 0; j < projects[i]["tags"].length; j++) {
        let tag = projects[i]["tags"][j]
        card_content += `<span class="badge text-bg-accent">${tag}</span>`
    }
    
    card_content += `</div>
    <p class="card-text">${projects[i]["description"]}</p>
    <a class="btn btn-outline-light align-self-start mt-auto" href="${projects[i]["url"]}" target="_blank">GitHub</a>
    </div>
    </div>
    </div>`;
    
    row.innerHTML += card_content;
}

function draw_cards(tag) {
    let cards = document.querySelectorAll(".project-card");
    for (let i = 0; i < cards.length; i++) {
        const card = cards[i];
        const card_tags = card.dataset.tags.split(",");

        if (tag == "all" || card_tags.includes(tag)) {
            card.classList.remove("d-none");
        } else {
            card.classList.add("d-none");
        }
    }
}
