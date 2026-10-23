"use strict";

const dashboardView = document.getElementById("dashboardView");
const lessonView = document.getElementById("lessonView");
const labView = document.getElementById("labView");

const moduleList = document.getElementById("moduleList");
const lessonContent = document.getElementById("lessonContent");
const labOutput = document.getElementById("labOutput");

function showView(view) {
    dashboardView.classList.add("hidden");
    lessonView.classList.add("hidden");
    labView.classList.add("hidden");

    view.classList.remove("hidden");
}

async function loadServerStatus() {
    const statusElement = document.getElementById("serverStatus");

    try {
        const response = await fetch("/status");

        if (!response.ok) {
            throw new Error("Server unavailable");
        }

        const data = await response.json();

        statusElement.textContent =
            `Server: ${data.status} | Database: ${data.database}`;

    } catch (error) {
        statusElement.textContent = "Server: OFFLINE";
    }
}

async function loadModules() {
    try {
        const response = await fetch("/lessons");

        if (!response.ok) {
            throw new Error("Unable to retrieve modules.");
        }

        const data = await response.json();

        moduleList.replaceChildren();

        data.modules.forEach(module => {
            const card = document.createElement("article");
            card.className = "module-card";

            const title = document.createElement("h3");
            title.textContent =
                `${String(module.id).padStart(2, "0")}. ${module.title}`;

            const difficulty = document.createElement("p");
            difficulty.textContent = `Difficulty: ${module.difficulty}`;

            const button = document.createElement("button");
            button.type = "button";

            if (module.id === 1) {
                button.textContent = "Start Lesson";
                button.addEventListener("click", () => {
                    loadLesson(module.id);
                });
            } else {
                button.textContent = "Coming Soon";
                button.disabled = true;
            }

            card.append(title, difficulty, button);
            moduleList.appendChild(card);
        });

    } catch (error) {
        moduleList.textContent = error.message;
    }
}

async function loadLesson(moduleId) {
    showView(lessonView);
    lessonContent.textContent = "Loading lesson...";

    try {
        const response = await fetch(`/lessons/${moduleId}`);

        if (!response.ok) {
            throw new Error("Unable to retrieve lesson.");
        }

        const lesson = await response.json();

        lessonContent.replaceChildren();

        const heading = document.createElement("h2");
        heading.textContent = lesson.title;
        lessonContent.appendChild(heading);

        const description = document.createElement("p");
        description.textContent = lesson.description;
        lessonContent.appendChild(description);

        lesson.sections.forEach(section => {
            const container = document.createElement("section");
            container.className = "lesson-section";

            const title = document.createElement("h3");
            title.textContent = section.title;

            const content = document.createElement("p");
            content.textContent = section.content;

            container.append(title, content);
            lessonContent.appendChild(container);
        });

        const practiceHeading = document.createElement("h3");
        practiceHeading.textContent = "Guided SQL Practice";
        lessonContent.appendChild(practiceHeading);

        lesson.guided_practice.forEach(exercise => {
            const section = document.createElement("section");
            section.className = "lesson-section";

            const instruction = document.createElement("p");
            instruction.textContent =
                `Step ${exercise.step}: ${exercise.instruction}`;

            const query = document.createElement("pre");
            query.textContent = exercise.query;

            const button = document.createElement("button");
            button.type = "button";
            button.textContent = `Open Lab ${exercise.step}`;

            button.addEventListener("click", () => {
                showView(labView);
                runLab(exercise.step);
            });

            section.append(instruction, query, button);
            lessonContent.appendChild(section);
        });

        const assessmentHeading = document.createElement("h3");
        assessmentHeading.textContent = "Knowledge Check";
        lessonContent.appendChild(assessmentHeading);

        const question = document.createElement("p");
        question.textContent = lesson.assessment.question;
        lessonContent.appendChild(question);

        const options = document.createElement("p");
        options.textContent = lesson.assessment.options.join(" | ");
        lessonContent.appendChild(options);

        const note = document.createElement("p");
        note.textContent =
            "Assessment grading and completion tracking are coming next.";
        lessonContent.appendChild(note);

    } catch (error) {
        lessonContent.textContent = error.message;
    }
}

async function runLab(labId) {
    labOutput.textContent = "Executing SQL exercise...";

    try {
        const response = await fetch(`/labs/${labId}`);

        if (!response.ok) {
            throw new Error("Unable to execute laboratory.");
        }

        const result = await response.text();
        labOutput.textContent = result;

    } catch (error) {
        labOutput.textContent = error.message;
    }
}

document.getElementById("dashboardBtn")
    .addEventListener("click", () => showView(dashboardView));

document.getElementById("modulesBtn")
    .addEventListener("click", () => showView(dashboardView));

document.getElementById("labsBtn")
    .addEventListener("click", () => showView(labView));

document.getElementById("backBtn")
    .addEventListener("click", () => showView(dashboardView));

document.querySelectorAll("[data-lab]").forEach(button => {
    button.addEventListener("click", () => {
        runLab(Number(button.dataset.lab));
    });
});

loadServerStatus();
loadModules();