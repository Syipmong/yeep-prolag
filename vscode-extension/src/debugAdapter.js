const { DebugSession, InitializedEvent, TerminatedEvent, StoppedEvent, OutputEvent } = require('vscode-debugadapter');
const { Subject } = require('await-notify');
const { spawn } = require('child_process');
const path = require('path');

class YeepDebugSession extends DebugSession {
    constructor() {
        super();
        this._configurationDone = new Subject();
        this._yeepProcess = null;
    }

    initializeRequest(response, args) {
        response.body = response.body || {};
        response.body.supportsConfigurationDoneRequest = true;
        response.body.supportsEvaluateForHovers = true;
        response.body.supportsStepBack = false;
        response.body.supportsSetVariable = false;
        response.body.supportsRestartFrame = false;
        response.body.supportsGotoTargetsRequest = false;
        response.body.supportsStepInTargetsRequest = false;
        response.body.supportsCompletionsRequest = false;
        response.body.supportsModulesRequest = false;
        response.body.supportsRestartRequest = false;
        response.body.supportsExceptionOptions = false;
        response.body.supportsValueFormattingOptions = false;
        response.body.supportsExceptionInfoRequest = false;
        response.body.supportTerminateDebuggee = true;
        response.body.supportsDelayedStackTraceLoading = false;
        response.body.supportsLogPoints = false;
        response.body.supportsTerminateThreadsRequest = false;
        response.body.supportsSetExpression = false;
        response.body.supportsTerminateRequest = true;
        response.body.completionTriggerCharacters = [];
        response.body.supportsBreakpointLocationsRequest = false;

        this.sendResponse(response);
        this.sendEvent(new InitializedEvent());
    }

    async configurationDoneRequest(response, args) {
        super.configurationDoneRequest(response, args);
        this._configurationDone.notify();
    }

    async launchRequest(response, args) {
        await this._configurationDone.wait(1000);

        const program = args.program;
        const yeepPath = args.yeepPath || 'yeep';
        const programArgs = args.args || [];

        this.sendEvent(new OutputEvent(`🚀 Starting Yeep program: ${program}\n`, 'stdout'));

        try {
            // Launch the Yeep process
            this._yeepProcess = spawn(yeepPath, [program, ...programArgs], {
                cwd: path.dirname(program),
                stdio: ['pipe', 'pipe', 'pipe']
            });

            // Handle stdout
            this._yeepProcess.stdout.on('data', (data) => {
                this.sendEvent(new OutputEvent(data.toString(), 'stdout'));
            });

            // Handle stderr
            this._yeepProcess.stderr.on('data', (data) => {
                this.sendEvent(new OutputEvent(data.toString(), 'stderr'));
            });

            // Handle process exit
            this._yeepProcess.on('close', (code) => {
                this.sendEvent(new OutputEvent(`\n✅ Yeep program finished with exit code: ${code}\n`, 'stdout'));
                this.sendEvent(new TerminatedEvent());
            });

            // Handle process error
            this._yeepProcess.on('error', (err) => {
                this.sendEvent(new OutputEvent(`❌ Error starting Yeep: ${err.message}\n`, 'stderr'));
                this.sendEvent(new TerminatedEvent());
            });

            this.sendResponse(response);

        } catch (error) {
            this.sendEvent(new OutputEvent(`❌ Failed to launch Yeep: ${error.message}\n`, 'stderr'));
            this.sendEvent(new TerminatedEvent());
            this.sendResponse(response);
        }
    }

    async disconnectRequest(response, args) {
        if (this._yeepProcess) {
            this._yeepProcess.kill();
        }
        this.sendResponse(response);
    }

    async terminateRequest(response, args) {
        if (this._yeepProcess) {
            this._yeepProcess.kill();
        }
        this.sendResponse(response);
    }
}

// Start the debug adapter
YeepDebugSession.run(YeepDebugSession);
