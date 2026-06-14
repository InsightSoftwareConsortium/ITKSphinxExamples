import breathe

from docutils import nodes
from docutils.parsers import rst
from docutils.parsers.rst import Directive


def breathe_choice(argument):
    """Option defining which breathe directive to use."""
    try:
        breathe_directives = list(breathe.DoxygenDirectiveFactory.directives.keys())
    except AttributeError:
        # Newer breathe releases do not expose DoxygenDirectiveFactory; the
        # directive name is validated by docutils when it is looked up.
        return argument

    return rst.directives.choice(argument, breathe_directives)


class BreathelinkDirective(Directive):

    required_arguments = 1
    optional_arguments = 100
    option_spec = {
        "breathe": breathe_choice,
        "doxylink": rst.directives.unchanged_required,
    }

    def run(self):
        config = self.state.document.settings.env.app.config
        if "breathe" in self.options:
            breathe_directive_name = self.options["breathe"]
        else:
            if "breathelinkstruct" in self.name:
                breathe_directive_name = config.breathelink_struct_breathe_directive
            else:
                breathe_directive_name = config.breathelink_default_breathe_directive
        if "doxylink" in self.options:
            doxylink_role_name = self.options["doxylink"]
        else:
            doxylink_role_name = config.breathelink_default_doxylink_role

        new_content = []
        for argument in self.arguments:
            arguments = [argument]
            options = {"no-link": ""}
            breathe_directive_class, messages = rst.directives.directive(
                breathe_directive_name, self.state.memo.language, self.state.document
            )
            self.state.parent += messages
            breathe_directive_instance = breathe_directive_class(
                breathe_directive_name,
                arguments,
                options,
                self.content,
                self.lineno,
                self.content_offset,
                self.block_text,
                self.state,
                self.state_machine,
            )
            new_content += breathe_directive_instance.run()

            list_item = nodes.generated("", "")
            list_item.reporter = self.state_machine.reporter
            doxylink_role_class, messages = rst.roles.role(
                doxylink_role_name,
                self.state.memo.language,
                self.lineno,
                self.state_machine.reporter,
            )
            self.state.parent += messages
            role_nodes, messages = doxylink_role_class(
                doxylink_role_name, "", arguments[0], self.lineno, list_item
            )
            # The reporter function is not picklable
            list_item.reporter = None
            self.state.parent += messages
            list_item += nodes.generated("", "See ")
            list_item += role_nodes
            list_item += nodes.generated("", " for additional documentation.")

            link = nodes.bullet_list("")
            link["bullet"] = "-"
            link += list_item
            new_content += link

        return new_content


def setup(app):

    app.add_config_value("breathelink_default_breathe_directive", "doxygenclass", True)
    app.add_config_value("breathelink_default_doxylink_role", "doxylink", True)
    app.add_config_value("breathelink_struct_breathe_directive", "doxygenstruct", True)

    app.add_directive("breathelink", BreathelinkDirective)
    app.add_directive("breathelinkstruct", BreathelinkDirective)

    return {
        "version": "0.2",
        "parallel_read_safe": True,
        "parallel_write_safe": True,
    }
