document.addEventListener('DOMContentLoaded', function() {
    const apiUrl = 'https://api.github.com/repos/Chihaya-Yuka/CSTL/commits';
    const newsContainer = document.getElementById('news');

    async function fetchLatestCommit() {
        try {
            const response = await fetch(apiUrl);
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            const commits = await response.json();
            if (commits.length === 0) {
                newsContainer.innerHTML = '<p>No recent news.</p>';
                return;
            }
            const latestCommit = commits[0];
            const commitInfo = `
                <h3>Latest Update</h3>
                <p><strong>Commit Message:</strong> ${latestCommit.commit.message}</p>
                <p><strong>Author:</strong> ${latestCommit.commit.author.name}</p>
                <p><strong>Date:</strong> ${latestCommit.commit.author.date}</p>
                <p><strong>Details:</strong> <a href="${latestCommit.html_url}" target="_blank">View Commit</a></p>
            `;
            newsContainer.innerHTML = commitInfo;
        } catch (error) {
            console.error('Error fetching commits:', error);
            newsContainer.innerHTML = '<p>Error loading news.</p>';
        }
    }

    fetchLatestCommit();
});