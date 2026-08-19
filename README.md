# ChatGPT Temporary Runner

This public repository is reserved for short-lived GitHub-hosted Ubuntu Runner tasks requested by the repository owner and prepared through ChatGPT.

## Operating policy

- Manual dispatch only; no `push`, `pull_request`, `schedule`, or external-event triggers.
- Default `GITHUB_TOKEN` permissions are read-only.
- No production deployment, package publishing, or long-running services.
- No repository or account secrets unless the owner explicitly adds a task-scoped secret.
- Each job must define a short timeout and upload only necessary artifacts.
- Task-specific workflow changes should be removed or reset after completion.

The baseline workflow only performs a runner health check. Task-specific build, test, browser, or screenshot steps may be temporarily substituted when needed.
