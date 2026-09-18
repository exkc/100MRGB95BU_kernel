import exhale
import exhale.configs
import exhale.utils
import exhale.deploy

import os
import os.path

def setup(app):
    pass

def exhale_environment_ready(app):
    default_project = app.config.breathe_default_project
    default_exhale_args = dict(app.config.exhale_args)

    exhale_projects_args = dict(app.config._raw_config['exhale_projects_args'])
    breathe_projects = dict(app.config._raw_config['breathe_projects'])

    for project in breathe_projects:
        app.config.breathe_default_project = project
        os.makedirs(breathe_projects[project], exist_ok=True)

        project_exhale_args = exhale_projects_args.get(project, {})

        app.config.exhale_args = dict(default_exhale_args)
        app.config.exhale_args.update(project_exhale_args)
        app.config.exhale_args["containmentFolder"] = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), app.config.exhale_args["containmentFolder"])

        # setup the extension and verify all of the configurations.
        exhale.configs.apply_sphinx_configurations(app)

        # Generate the full API!
        try:
            if project != "api":
                exhale.deploy.explode()
        except:
            exhale.utils.fancyError("Exhale: could not generate reStructuredText documents :/")

    app.config.breathe_default_project = default_project

exhale.environment_ready = exhale_environment_ready
