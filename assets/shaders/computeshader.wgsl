@group(0) @binding(0)
var<storage,read> inputBuffer: array<f32>;

@group(0) @binding(1)
var<storage,read_write> outputBuffer: array<f32>;

@compute @workgroup_size(32)
fn computeStuff(@builtin(global_invocation_id) threadId: vec3u) {
    outputBuffer[threadId.x] = 2.0 * inputBuffer[threadId.x];
}
