 
# ARIES

<div align="center">

![ARIES Logo](/.github/logo.png)
</div>

**ARIES** (Annotation & Reasoning Intelligent Engineering Suite) is an Integrated Development Environment (IDE) specifically designed for **CoT (Chain-of-Thought)** data annotation and prompt engineering. This tool aims to help researchers and developers efficiently build, optimize, and manage prompt engineering workflows through an intuitive interface and powerful features, enhancing the performance of large language models (LLMs).

---

## Project Background

With the rapid development of large language models (e.g., the GPT series), **Prompt Engineering** has become a critical technique for improving the task-specific capabilities of these models. ARIES focuses on addressing the following core challenges:

- Efficient annotation of Chain-of-Thought data for model fine-tuning or prompt optimization;
- Rapid iteration of complex prompts to enhance model performance on specific tasks;
- Providing a unified tool that integrates data annotation, prompt debugging, and experiment management functionalities.

Whether it's researchers exploring new reasoning chain methodologies or industrial-scale data annotation, ARIES significantly boosts productivity.

---

## Core Features

ARIES provides the following core modules:

1. **CoT Data Annotation**
   - Intuitive annotation interface supporting multiple formats (text, JSON, etc.).
   - Automated annotation assistance to reduce repetitive work and improve consistency.

2. **Prompt IDE**
   - A dedicated editor optimized for prompt engineering, supporting multiple languages (Python, JSON, etc.).
   - Features syntax highlighting, auto-completion, and error detection.
   - Built-in prompt debugging tools to view real-time model responses.

3. **Data Visualization**
   - Built-in visualization tools to analyze prompt effectiveness and model performance.
   - Supports comparative experiment results to quickly identify issues and optimize prompts.

4. **Version Control**
   - Provides prompt version management to easily track iteration history.
   - Git integration for seamless team collaboration and code synchronization.

5. **Plugin Support**
   - Plugin architecture for user-defined extensions.
   - Integration with mainstream large language model APIs (e.g., OpenAI GPT, Anthropic Claude).

---

## Installation Guide

### System Requirements
Before installing ARIES, ensure your system meets the following requirements:
- **Operating System**: Windows / macOS / Linux
- **Python**: Version ≥ 3.8
- **Required Tools**: Git, pip

### Installation Steps

1. Clone the project repository:
```bash
git clone https://github.com/Chihaya-Yuka/ARIES.git
cd ARIES
```

2. Install Python dependencies:
```bash
pip install -r requirements.txt
```

3. Launch the application:
```bash
python app.py
```

4. Open in your browser:
```
http://localhost:8000
```

---

## User Guide

### 1. CoT Data Annotation
After launching the project, navigate to the "Annotation" module:
- Import your data files (supports JSON/CSV/TXT formats).
- Select the data range to annotate.
- Begin manual or semi-automatic annotation.

### 2. Prompt Development and Debugging
Go to the "Prompt IDE" module:
- Create or import existing prompt files.
- Use the editor features to write or optimize prompts.
- Click the "Test" button to view real-time model responses and adjust prompts as needed.

### 3. Analysis and Visualization
In the "Analysis" module:
- View CoT reasoning paths and performance metrics of the model.
- Compare the effectiveness of different prompts to choose the best approach.

---

## Contribution Guide

We welcome community developers to contribute to ARIES! Here’s how you can get involved:

1. Submit Issues:
   - If you encounter bugs or have feature suggestions, please submit an issue on GitHub.

2. Fork & Pull Request:
   - Fork this repository, make changes on your branch, and submit a pull request once complete.

3. Discuss & Support:
   - Join our community discussions to share your experiences and suggestions for improvement.

---

## Future Plans

We plan to release the following features in the future:
- **Multi-User Collaboration**: Support for real-time collaborative annotation and development.
- **Enhanced Automation**: Development of intelligent annotation suggestions and prompt optimization tools based on LLMs.
- **Support for More Model APIs**: Expand support for Hugging Face and other LLM platforms.
- **Performance Monitoring Module**: Provide more detailed performance analysis and monitoring tools.

---

With ARIES, unlock the potential of prompt engineering and make CoT data annotation and optimization easier and more efficient! ✨
